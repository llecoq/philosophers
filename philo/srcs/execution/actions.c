/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:02:40 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/16 14:07:29 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	take_fork(t_philosopher *philosopher, pthread_mutex_t *fork, long *timestamp)
{
	pthread_mutex_lock(fork);
	*timestamp = get_timestamp(philosopher->parameters->starting_time);
	print_action(*timestamp, philosopher->philosopher_nb, HAS_TAKEN_A_FORK);
}

void	drop_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->fork);
	pthread_mutex_unlock(philosopher->next_fork);
}

void	philo_sleep(t_philosopher *philosopher, long starting_time, long time_to_sleep)
{
	long	timestamp;

	timestamp = get_timestamp(philosopher->parameters->starting_time);
	print_action(timestamp, philosopher->philosopher_nb, IS_SLEEPING);
	timestamp = oversleep_is_for_the_weak(starting_time, timestamp, time_to_sleep);
	print_action(timestamp, philosopher->philosopher_nb, IS_THINKING);
}

void	philo_eat(t_philosopher *philosopher, long starting_time, long time_to_eat)
{
	long	timestamp;

	take_fork(philosopher, &philosopher->fork, &timestamp);
	take_fork(philosopher, philosopher->next_fork, &timestamp);
	print_action(timestamp, philosopher->philosopher_nb, IS_EATING);
	oversleep_is_for_the_weak(starting_time, timestamp, time_to_eat);
	drop_forks(philosopher);
}
