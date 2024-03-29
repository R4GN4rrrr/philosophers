/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:21:08 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/06/09 20:41:57 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_rules
{
	int					nb_philo;
	long				t_to_die;
	long int			t_to_eat;
	long int			t_to_sleep;
	int					nb_must_eat;
	long				t_current;
	int					meals;
	int					id;
	long				*last_eat;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_t			*philo;
}	t_rules;

/* ------------- utils ------------- */
int		exit_error(void);
int		ft_atoi(char *str);
int		check_args(char **av);
void	print(t_rules *philo, char *str, long time, int id);
/* ------------- init ------------- */
int		check_death(t_rules *philo);
int		init_rules(char **av, t_rules *rules);
int		init_philo(t_rules *rules);
void	*routine(void *arg);
/* ------------- time ------------- */
long	current_time(t_rules *philo);
long	ft_time(void);
void	sleep_time(long t_to_sleep);

#endif