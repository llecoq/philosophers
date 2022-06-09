/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:29:26 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/21 15:14:45 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

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

int	destroy_mutex(t_philosopher *philosopher, t_parameters *parameters)
{
	int	i;

	usleep(10000);
	i = -1;
	while (++i < parameters->nb_of_philosophers)
		if (pthread_mutex_destroy(&philosopher[i].fork) >= FAILED)
			return (FAILED);
	pthread_mutex_unlock(&parameters->print_action_mutex);
	if (pthread_mutex_destroy(&parameters->print_action_mutex) >= FAILED)
		return (FAILED);
	if (pthread_mutex_destroy(&parameters->had_a_meal_mutex) >= FAILED)
		return (FAILED);
	if (pthread_mutex_destroy(&parameters->starting_time_mutex) >= FAILED)
		return (FAILED);
	return (SUCCESS);
}

int	clean_exit_mutex(t_philosopher *philosopher, int i, int action)
{
	if (action == CREATE)
		while (--i <= 0)
			pthread_mutex_destroy(&philosopher[i].fork);
	else if (action == DETACH)
	{
		i = -1;
		while (++i < philosopher->parameters->nb_of_philosophers)
			pthread_mutex_destroy(&philosopher[i].fork);
	}
	pthread_mutex_destroy(&philosopher->parameters->had_a_meal_mutex);
	pthread_mutex_destroy(&philosopher->parameters->print_action_mutex);
	pthread_mutex_destroy(&philosopher->parameters->starting_time_mutex);
	return (EXECUTION_ERROR);
}
