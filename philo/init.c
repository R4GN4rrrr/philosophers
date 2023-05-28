/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:59:21 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/05/28 02:07:38 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pihlo.h"

void *routine(void *arg)
{
	pthread_mutex_t right;
	pthread_mutex_t left;
	t_rules *philo;

	philo = (t_rules *) arg;
	right = philo->forks[philo->id];
	left = philo->forks[(philo->id) % philo->nb_philo];
	pthread_mutex_lock(&right);
	print(philo, "has taken a fork\n",current_time(philo));
	pthread_mutex_lock(&left);
	print(philo, "has taken a fork\n",current_time(philo));
	print(philo, "is eating\n", current_time(philo));
	// pthread_mutex_lock(&philo->mutex);
	// philo->last_eat[philo->id] = current_time(philo);
	// pthread_mutex_unlock(&philo->mutex);
	printf("t_toeat: %ld\n", philo->t_to_eat);
	sleep_time(philo->t_to_eat);
	// pthread_mutex_lock(&philo->mutex);
	// philo->meals++;
	// pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&right);
	pthread_mutex_unlock(&left);
	return(0);
}

int	check_death(t_rules *philo)
{
	int i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&philo->mutex);
		if (philo->nb_must_eat != -1 && philo->nb_must_eat * philo->nb_philo == philo->meals)
			return (0);
		while (i < philo->nb_philo)
		{
			if (current_time(philo) - philo->last_eat[philo->id] >= philo->t_to_die)
			{
				print(philo, "is dead\n", current_time(philo));
				return (1);
			}
			i++;
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	return (0);
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
	rules->id = 0;
	rules->meals = 0;
	rules->t_current = ft_time();
	if (!rules->forks)
		return (1);
	return (0);
}

int init_philo(t_rules *rules)
{
	int i;
	
	i = 0;

	pthread_mutex_init(&rules->mutex, NULL);
	pthread_mutex_init(&rules->print, NULL);
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		rules->id = i;
		if (pthread_create(&rules->philo[i], NULL, &routine, rules))
		{
			printf("Error\n, Creation failed!!");
			return (1);
		}
		usleep(100);
		i += 2;
	}
	usleep(500);
	i  = 1;
	while (i < rules->nb_philo)
	{
		rules->id = i;
		if (pthread_create(&rules->philo[i], NULL, &routine, rules))
		{
			printf("Error\n, Creation failed!!");
			return (1);
		}
		usleep(100);
		i += 2;
	}
	i  = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_join(rules->philo[i], NULL) != 0)
		{
			printf("Error\n, Creation failed!!");
			return (1);
		}
		i++;
	}
	// pthread_mutex_destroy(&rules->mutex);
	return (0);
}