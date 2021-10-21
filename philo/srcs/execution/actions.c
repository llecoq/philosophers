/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:02:40 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/21 13:46:52 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

// int	last_meal_time(t_philosopher *philosopher)
// {
// 	long	time_to_die;
// 	long	last_meal_time;
// 	long	timestamp;
// 	long	time_diff;

// 	time_to_die = philosopher->parameters->time_to_die;
// 	last_meal_time = philosopher->last_meal_time;
// 	timestamp = philosopher->parameters->timestamp;
// 	time_diff = timestamp - last_meal_time;
// 	if (time_diff > time_to_die)
// 	{
// 		print_action(philosopher, philosopher->philosopher_nb, DIED);
// 		philosopher->philosopher_status = DEAD;
// 		philosopher->parameters->status = DEAD;
// 		return (TIME_TO_DIE);
// 	}
// 	return (ALIVE);
// }

void	take_fork(t_philosopher *philosopher, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	philosopher->nb_of_forks++;
	print_action(philosopher, philosopher->philosopher_nb, HAS_TAKEN_A_FORK);
}

void	drop_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->fork);
	philosopher->nb_of_forks--;
	pthread_mutex_unlock(philosopher->next_fork);
	philosopher->nb_of_forks--;
}

void	philo_eat(t_philosopher *philosopher)
{
	take_fork(philosopher, &philosopher->fork);
	take_fork(philosopher, philosopher->next_fork);
	print_action(philosopher, philosopher->philosopher_nb, IS_EATING);
	oversleep_is_for_the_weak(philosopher, philosopher->parameters->time_to_eat);
	drop_forks(philosopher);
	if (philosopher->parameters->nb_of_meals >= IS_SET)
	{
		philosopher->nb_of_meals_to_eat--;
		if (philosopher->nb_of_meals_to_eat == 0)
		{
			pthread_mutex_lock(&philosopher->parameters->had_a_meal_mutex);
			philosopher->parameters->nb_of_philosophers_done_eating++;
			pthread_mutex_unlock(&philosopher->parameters->had_a_meal_mutex);
		}
	}
}

void	philo_sleep(t_philosopher *philosopher)
{
	print_action(philosopher, philosopher->philosopher_nb, IS_SLEEPING);
	oversleep_is_for_the_weak(philosopher, philosopher->parameters->time_to_sleep);
	print_action(philosopher, philosopher->philosopher_nb, IS_THINKING);
}
