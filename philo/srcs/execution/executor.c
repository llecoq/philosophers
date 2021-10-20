/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:53:14 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/20 14:59:50 by llecoq           ###   ########.fr       */
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

void	*philosophize_or_die(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	wait_for_all_threads(philosopher);
	if (philosopher->philosopher_nb % 2 > 0)
		usleep(500);
	while (philosopher->parameters->status != DEAD)
	{
		if (philosopher->parameters->status == DEAD)
			break ;
		philo_eat(philosopher);
		if (philosopher->philosopher_status != DEAD)
			philo_sleep(philosopher);
	}
	return (NULL);
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
	}
	set_starting_time(parameters);
	death_monitor((t_philosopher *)&philo);
	// death_vs_time((t_philosopher *)&philo, parameters);
	// while (--i >= 0)
	// {
	// 	if (pthread_join(philo[i].id, NULL) >= FAILED)
	// 		return (EXECUTION_ERROR);
	// }
	return (EXIT_SUCCESS);
}
