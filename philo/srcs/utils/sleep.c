/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:07:40 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/16 20:03:45 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static long	get_time_diff(t_parameters *parameters, long timestamp)
{
	long	time_diff;

	time_diff = parameters->timestamp - timestamp;
	return (time_diff);
}

void	oversleep_is_for_the_weak(t_philosopher *philosopher, long sleep_time)
{
	long	time_diff;
	long	timestamp;

	timestamp = philosopher->timestamp;
	usleep(sleep_time * 500);
	time_diff = get_time_diff(philosopher->parameters, timestamp);
	while (time_diff < sleep_time)
		time_diff = get_time_diff(philosopher->parameters, timestamp);
	philosopher->timestamp = timestamp + sleep_time;
}
