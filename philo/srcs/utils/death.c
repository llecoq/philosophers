/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:39:07 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/20 14:40:59 by llecoq           ###   ########.fr       */
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

void	death_monitor(t_philosopher *philosopher)
{
	long			time_to_die;
	int				nb_of_philosophers;
	int				i;

	time_to_die = philosopher[0].parameters->time_to_die;
	nb_of_philosophers = philosopher[0].parameters->nb_of_philosophers;
	while (1)
	{
		i = -1;
		while (++i < nb_of_philosophers)
			if (last_meal_time(philosopher[i], time_to_die) > TIME_TO_DIE)
				break ;
	}
}
