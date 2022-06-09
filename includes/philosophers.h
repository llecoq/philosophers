/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:59:21 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/21 15:24:50 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/errno.h>
# include "enum.h"

typedef struct s_parameters
{
	pthread_mutex_t	print_action_mutex;
	pthread_mutex_t	had_a_meal_mutex;
	pthread_mutex_t	starting_time_mutex;
	int				nb_of_philosophers;
	int				philosophers_done_eating;
	int				status;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_meals;
	long			starting_time;
}					t_parameters;

typedef struct s_philosopher
{
	pthread_t		id;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	t_parameters	*parameters;
	int				philosopher_nb;
	int				nb_of_meals_to_eat;
	int				nb_of_forks;
	long			last_meal_time;
	long			last_action_time;
}					t_philosopher;

/* ------------------EXECUTION------------------ */
int		execution(t_parameters *parameters);
void	philo_sleep(t_philosopher *philosopher);
void	philo_eat(t_philosopher *philosopher);

/* -------------------PARSING------------------- */

int		parse(t_parameters *parameters, int argc, char **argv);

/* --------------------UTILS-------------------- */

int		error(int error_type, char *arg);
int		error_clear(int error_type);
long	ft_atoi(const char *str);
long	get_timestamp(t_parameters *parameters);
void	oversleep_is_for_the_weak(t_philosopher *philosopher, long sleep_time);
void	print_action(t_philosopher *philo, int philosopher_nb, int action);
void	set_starting_time(t_parameters *parameters);
void	life_vs_death_monitor(t_philosopher *philosopher);

/* --------------------MUTEX-------------------- */

int		destroy_mutex(t_philosopher *philosopher, t_parameters *parameters);
int		clean_exit_mutex(t_philosopher *philosopher, int i, int action);
void	clean_unlock_mutex(t_philosopher *philosopher);

#endif