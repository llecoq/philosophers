/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:53:14 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/16 20:02:03 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	init_philosopher(t_philosopher *philo, t_parameters *parameters)
{
	int	i;
	int nb_of_philosophers;

	nb_of_philosophers = parameters->nb_of_philosophers;
	i = -1;
	while (++i <= nb_of_philosophers)
	{
		philo[i].parameters = parameters;
		philo[i].timestamp = 0;
		philo[i].philosopher_nb = i;
		philo[i].philosopher_status = ALIVE;
		philo[i].nb_of_meals_to_eat = parameters->nb_of_meals;
		philo[i].last_meal_time = 0;
		if (pthread_mutex_init(&philo[i].fork, NULL) >= FAILED)
		{
			//clear zooob
			return ;
		}
	}
	philo[--i].next_fork = &philo[1].fork;
	while (--i > 0)
		philo[i].next_fork = &philo[i + 1].fork;
}

void	set_starting_time(t_parameters *parameters)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		return ; // zob erreur
	parameters->starting_time = time.tv_sec * 1000000 + time.tv_usec;
	parameters->starting_time *= 0.001;
}

void	run_timestamp(t_parameters *parameters)
{
	struct timeval	time;
	long			timestamp;
	long			starting_time;

	starting_time = parameters->starting_time;
	while (1)
	{
		if (gettimeofday(&time, NULL) == -1)
			return ; // zob erreur
		timestamp = (time.tv_sec * 1000000 + time.tv_usec) * 0.001 - starting_time;
		parameters->timestamp = timestamp;
		usleep(800);
	}
}

void	*philosophize_or_die(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->philosopher_nb == 0)
		run_timestamp(philosopher->parameters);
	if (philosopher->philosopher_nb % 2 == 0)
		usleep(500);
	// usleep(philosopher->philosopher_nb * 100);
	while (philosopher->philosopher_status != DEAD)
	{
		if (philosopher->parameters->status == DEAD)
			break ;
		philo_eat(philosopher);
		if (philosopher->philosopher_status != DEAD)
			philo_sleep(philosopher);
	}
	return (NULL);
}

void	death_checker(t_parameters *parameters)
{
	while (1)
	{
		if (parameters->status == DEAD)
			break ;
		usleep(105000);
	}
}

// refaire la sync des threads ?
int	execution(t_parameters *parameters)
{
	int				i;
	t_philosopher	philo[400];

	init_philosopher((t_philosopher *)&philo, parameters);
	set_starting_time(parameters);
	i = -1;
	while (++i <= parameters->nb_of_philosophers)
	{
		if (pthread_create(&philo[i].id, NULL, &philosophize_or_die, &philo[i])
			>= FAILED)
			// return (error(PTHREAD FAILED));
			return (EXECUTION_ERROR);
	}
	death_checker(parameters);
	while (--i >= 0)
	{
		if (pthread_join(philo[i].id, NULL) >= FAILED)
			return (EXECUTION_ERROR);
	}
	return (EXIT_SUCCESS);
}
