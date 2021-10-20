/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:53:14 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/20 17:31:18 by llecoq           ###   ########.fr       */
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
		philo[i].nb_of_forks = 0;
		philo[i].last_meal_time = 0;
		philo[i].last_action_time = NOT_SET;
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

void	wait_for_all_threads(t_philosopher *philosopher)
{
	while (1)
		if (philosopher->parameters->starting_time >= IS_SET)
			break ;
}

void	clean_unlock_mutex(t_philosopher *philosopher)
{
	if (philosopher->nb_of_forks == 1)
		pthread_mutex_unlock(philosopher->next_fork);
	else if (philosopher->nb_of_forks == 2)
	{
		pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(philosopher->next_fork);
	}
}

void	*philosophize_or_die(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	wait_for_all_threads(philosopher);
	if (philosopher->philosopher_nb % 2 > 0)
		usleep(500);
	while (philosopher->parameters->status != DEAD)
	{
		philo_eat(philosopher);
		philo_sleep(philosopher);
	}
	clean_unlock_mutex(philosopher);
	return (NULL);
}


void	destroy_mutex(t_philosopher *philosopher, t_parameters *parameters)
{
	int	i;

	i = -1;
	while (++i < parameters->nb_of_philosophers)
		if (pthread_mutex_destroy(&philosopher[i].fork) >= FAILED)
			return ; // ZOB
	pthread_mutex_destroy(&parameters->print_action);
}

// refaire la sync des threads ?
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
		pthread_detach(philo[i].id);
	}
	set_starting_time(parameters);
	life_vs_death_monitor((t_philosopher *)&philo);
	destroy_mutex((t_philosopher *)&philo, parameters);
	return (EXIT_SUCCESS);
}
