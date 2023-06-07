/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:22:42 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/07 02:46:39 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pihlo.h"

int	main(int ac, char **av)
{
	(void)av;

	t_rules info;
	if (ac < 5 || ac > 6)
		return(exit_error());
	if (check_Args(av))
		return 1;
	if (init_rules(av, &info))
		return 1;
	if (init_philo(&info))
		return 1;
	// if (check_death(&info))
	// 	return (1);
	int i  = 0;
	while (i < info.nb_philo)
	{
		if (pthread_join(info.philo[i], NULL) != 0)
		{
			printf("Error\n, Creation failed!!");
			return (1);
		}
		i++;
	}
}