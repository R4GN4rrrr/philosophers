/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:59:21 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/09 22:26:41 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	norm(t_rules *philo, pthread_mutex_t *right,
	pthread_mutex_t *left, long id)
{
	pthread_mutex_lock(right);
	print(philo, "has taken a fork\n", current_time(philo), id);
	pthread_mutex_lock(left);
	print(philo, "has taken a fork\n", current_time(philo), id);
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat[id] = current_time(philo);
	pthread_mutex_unlock(&philo->mutex);
	print(philo, "is eating\n", current_time(philo), id);
	sleep_time(philo->t_to_eat);
	pthread_mutex_lock(&philo->mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
	sleep_time(philo->t_to_sleep);
	print(philo, "is sleeeping\n", current_time(philo), id);
	print(philo, "is thinking\n", current_time(philo), id);
}

void	*routine(void *arg)
{
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	t_rules			*philo;
	long			id;

	philo = (t_rules *) arg;
	right = philo->forks + philo->id;
	left = philo->forks + (philo->id + 1) % philo->nb_philo;
	pthread_mutex_lock(&philo->mutex);
	id = (long)philo->id;
	pthread_mutex_unlock(&philo->mutex);
	while (1)
		norm(philo, right, left, id);
}

int	check_nb_must_eat(t_rules *philo)
{
	int	j;

	pthread_mutex_lock(&philo->mutex);
	if (philo->nb_must_eat != -1
		&& philo->nb_must_eat * philo->nb_philo == philo->meals)
	{
		j = 0;
		while (j < philo->nb_philo)
		{
			pthread_detach(philo->philo[j]);
			j++;
		}
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (0);
}

int	check_death(t_rules *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		if (check_nb_must_eat(philo))
			return (1);
		pthread_mutex_lock(&philo->mutex);
		while (i < philo->nb_philo)
		{
			if ((current_time(philo) - philo->last_eat[i]) >= philo->t_to_die)
			{
				pthread_mutex_lock(&philo->print);
				printf("%ld ms : Philo %d %s",
					current_time(philo), i + 1, "is dead\n");
				return (1);
			}
			i++;
		}
		pthread_mutex_unlock(&philo->mutex);
	}
}

int	init_rules(char **av, t_rules *rules)
{
	rules->nb_philo = (ft_atoi(av[1]));
	if (rules->nb_philo > 200 || rules->nb_philo < 1)
		return (printf("More 200 philosofers or None\n"));
	rules->t_to_die = (ft_atoi(av[2]));
	rules->t_to_eat = (ft_atoi(av[3]));
	rules->t_to_sleep = (ft_atoi(av[4]));
	if (rules->t_to_die < 60 || rules->t_to_eat < 60 || rules->t_to_sleep < 60)
		return (printf("lower than 60 ms\n"));
	if (av[5])
		rules->nb_must_eat = (ft_atoi(av[5]));
	else
		rules->nb_must_eat = -1;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	rules->philo = malloc(rules->nb_philo * sizeof(pthread_t));
	rules->t_current = ft_time();
	if (!rules->forks)
		return (1);
	return (0);
}
