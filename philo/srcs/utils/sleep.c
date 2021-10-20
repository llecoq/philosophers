/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:07:40 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/20 14:58:48 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static long	get_time_diff(t_parameters *parameters, long last_action_time)
{
	long	time_diff;
	long	timestamp;

	timestamp = get_timestamp(parameters);
	time_diff = timestamp - last_action_time;
	return (time_diff);
}

void	oversleep_is_for_the_weak(t_philosopher *philosopher, long sleep_time)
{
	long	time_diff;
	long	last_action_time;

	last_action_time = philosopher->last_action_time;
	time_diff = get_time_diff(philosopher->parameters, last_action_time);
	while (philosopher->philosopher_status == ALIVE)
	{
		time_diff = get_time_diff(philosopher->parameters, last_action_time);
		if (time_diff >= sleep_time)
			break;
		usleep(100);
	}
}
