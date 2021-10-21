/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:53:14 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/21 15:08:17 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	init_philosopher(t_philosopher *philo, t_parameters *parameters)
{
	int	i;
	int	nb_of_philosophers;

	nb_of_philosophers = parameters->nb_of_philosophers;
	i = -1;
	if (pthread_mutex_lock(&parameters->starting_time_mutex) >= FAILED)
		return (FAILED);
	while (++i < nb_of_philosophers)
	{
		philo[i].parameters = parameters;
		philo[i].philosopher_nb = i;
		philo[i].nb_of_meals_to_eat = parameters->nb_of_meals;
		philo[i].nb_of_forks = 0;
		philo[i].last_meal_time = 0;
		philo[i].last_action_time = NOT_SET;
		if (pthread_mutex_init(&philo[i].fork, NULL) >= FAILED)
			return (FAILED);
	}
	philo[--i].next_fork = &philo[0].fork;
	while (--i >= 0)
		philo[i].next_fork = &philo[i + 1].fork;
	return (SUCCESS);
}

void	wait_for_all_threads(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->parameters->starting_time_mutex);
	pthread_mutex_unlock(&philosopher->parameters->starting_time_mutex);
	while (1)
	{
		if (get_timestamp(philosopher->parameters) >= 0)
			break ;
	}
}

void	*philosophize_or_die(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	wait_for_all_threads(philosopher);
	if (philosopher->philosopher_nb % 2 > 0)
		usleep(500);
	while (1)
	{
		philo_eat(philosopher);
		philo_sleep(philosopher);
	}
	clean_unlock_mutex(philosopher);
	return (NULL);
}

int	execution(t_parameters *parameters)
{
	int				i;
	t_philosopher	philo[201];

	if (init_philosopher((t_philosopher *)&philo, parameters) == FAILED)
		return (EXECUTION_ERROR);
	i = -1;
	while (++i < parameters->nb_of_philosophers)
	{
		if (pthread_create(&philo[i].id, NULL, &philosophize_or_die, &philo[i])
			>= FAILED)
			return (clean_exit_mutex((t_philosopher *)&philo, i, CREATE));
		if (pthread_detach(philo[i].id) >= FAILED)
			return (clean_exit_mutex((t_philosopher *)&philo, i, DETACH));
	}
	set_starting_time(parameters);
	life_vs_death_monitor((t_philosopher *)&philo);
	if (destroy_mutex((t_philosopher *)&philo, parameters) == FAILED)
		return (EXECUTION_ERROR);
	return (EXIT_SUCCESS);
}
