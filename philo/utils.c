/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:48:08 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/07 01:38:47 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pihlo.h"

void	print(t_rules *philo, char *str, long time, int id)
{
	pthread_mutex_lock(&philo->print);
	printf("%ld ms : Philo %d %s", time, id + 1, str);
	pthread_mutex_unlock(&philo->print);
}
int	exit_error(void)
{
	printf("Error in Params please enter: nb_philo\
	time_to_die time_to_eat time_to_sleep (nb_must_eat)\n");
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (sign * nb);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}
int	check_Args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		
		if (!is_digit(av[i]))
		{
			write(2, "must be digits\n", 16);
			return (1);
		}
		i++;
	}
	return (0);
}
