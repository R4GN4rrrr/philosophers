/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:22:42 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/09 04:17:26 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	main(int ac, char **av)
// {
// 	(void)av;
// 	t_rules *rules;

//     rules = malloc(sizeof(t_rules));
// 	if (ac < 5 || ac > 6)
// 		return(exit_error());
// 	if (check_Args(av))
// 		return 1;
// 	if (init_rules(av, info))
// 		return 1;
// 	if (init_philo(info))
// 		return 1;
// 	return (check_death(&info));
// }
int	main(int ac, char **av)
{
	(void)av;
	int		i;
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (ac < 5 || ac > 6)
		return (exit_error());
	if (check_args(av))
		return (1);
	if (init_rules(av, rules))
		return (1);
	i = 0;
	pthread_mutex_init(&rules->mutex, NULL);
	pthread_mutex_init(&rules->print, NULL);
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	i = 0;
	rules->last_eat = malloc(sizeof(long) * rules->nb_philo);
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->mutex);
		rules->id = i;
		rules->last_eat[i] = current_time(rules);
		pthread_mutex_unlock(&rules->mutex);
		if (pthread_create(&rules->philo[i], NULL, &routine, rules))
		{
			printf("Error\n, Creation failed!!");
			return (1);
		}
		usleep(100);
		i++;
	}
	return (check_death(rules));
}
