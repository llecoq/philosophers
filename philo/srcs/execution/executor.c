/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:53:14 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/16 14:44:43 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	init_philosopher(t_philosopher *philo, t_parameters *parameters)
{
	int	i;
	int nb_of_philosophers;

	nb_of_philosophers = parameters->nb_of_philosophers;
	i = -1;
	while (++i < nb_of_philosophers)
	{
		philo[i].parameters = parameters;
		philo[i].philosopher_nb = i;
		philo[i].philosopher_status = ALIVE;
		philo[i].nb_of_meals_to_eat = parameters->nb_of_meals;
		if (pthread_mutex_init(&philo[i].fork, NULL) >= FAILED)
		{
			//clear zooob
			return ;
		}
	}
	philo[--i].next_fork = &philo[0].fork;
	while (--i >= 0)
		philo[i].next_fork = &philo[i + 1].fork;
}

void	set_starting_time(t_parameters *parameters)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		return ; // zob erreur
	parameters->starting_time = time.tv_sec * 1000000 + time.tv_usec;
	parameters->starting_time /= 1000;
}

void	wait_for_all_threads(t_parameters *parameters)
{
	while (1)
		if (parameters->starting_time >= IS_SET)
			break ;
}

void	*philosophize_or_die(void *arg)
{
	t_philosopher	*philosopher;
	long			starting_time;
	long			time_to_eat;
	long			time_to_sleep;

	philosopher = (t_philosopher *)arg;
	starting_time = philosopher->parameters->starting_time;
	time_to_eat = philosopher->parameters->time_to_eat;
	time_to_sleep = philosopher->parameters->time_to_sleep;
	wait_for_all_threads(philosopher->parameters);
	if (philosopher->philosopher_nb % 2 > 0)
		usleep(1000);
	while (philosopher->philosopher_status != DEAD)
	{
		philo_eat(philosopher, starting_time, time_to_eat);
		philo_sleep(philosopher, starting_time, time_to_sleep);
	}
	return (NULL);
}

int	execution(t_parameters *parameters)
{
	int				i;
	t_philosopher	philo[400];

	init_philosopher((t_philosopher *)&philo, parameters);
	i = -1;
	while (++i < parameters->nb_of_philosophers)
	{
		if (pthread_create(&philo[i].id, NULL, &philosophize_or_die, &philo[i])
			>= FAILED)
			// return (error(PTHREAD FAILED));
			return (EXECUTION_ERROR);
	}
	set_starting_time(parameters); // attendre qu'ils soient tous cree
	while (--i >= 0)
	{
		if (pthread_join(philo[i].id, NULL) >= FAILED)
			return (EXECUTION_ERROR);
	}
	return (EXIT_SUCCESS);
}
