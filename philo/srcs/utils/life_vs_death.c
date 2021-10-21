/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_vs_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:39:07 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/21 15:21:12 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	last_meal_time(t_philosopher philosopher, long time_to_die)
{
	long	time_diff;
	long	timestamp;
	long	last_meal_time;

	timestamp = get_timestamp(philosopher.parameters);
	last_meal_time = philosopher.last_meal_time;
	time_diff = timestamp - last_meal_time;
	if (time_diff > time_to_die)
	{
		print_action(&philosopher, philosopher.philosopher_nb, DIED);
		return (TIME_TO_DIE);
	}
	return (ALIVE);
}

void	life_vs_death_monitor(t_philosopher *philo)
{
	long			time_to_die;
	int				nb_of_philosophers;
	int				done_eating;
	int				i;

	time_to_die = philo->parameters->time_to_die;
	nb_of_philosophers = philo->parameters->nb_of_philosophers;
	while (1)
	{
		i = -1;
		while (++i < nb_of_philosophers)
		{
			pthread_mutex_lock(&philo->parameters->had_a_meal_mutex);
			done_eating = philo->parameters->philosophers_done_eating;
			if (done_eating == nb_of_philosophers)
			{
				pthread_mutex_unlock(&philo->parameters->had_a_meal_mutex);
				return ;
			}
			pthread_mutex_unlock(&philo->parameters->had_a_meal_mutex);
			if (last_meal_time(philo[i], time_to_die) == TIME_TO_DIE)
				return ;
		}
	}
}
