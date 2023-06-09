/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:50:34 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/09 02:42:57 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pihlo.h"

long	ft_time(void)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec * 1000 + curr.tv_usec / 1000));
}

long	current_time(t_rules *philo)
{
	return (ft_time() - philo->t_current);
}

void	sleep_time(long t_to_sleep)
{
	long	start_time;

	start_time = ft_time();
	while (ft_time() - start_time < t_to_sleep)
		usleep(50);
}
