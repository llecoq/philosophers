/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:07:40 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/16 14:07:59 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

long	get_timestamp(long starting_time)
{
	struct timeval	time;
	long			timestamp;

	if (gettimeofday(&time, NULL) == -1)
		return (-1); // zob erreur
	timestamp = (time.tv_sec * (long)1000000 + time.tv_usec) / (long)1000;
	timestamp -= starting_time;
	return (timestamp);
}

static long	get_time_diff(long starting_time, long timestamp)
{
	long	time_diff;
	long	new_timestamp;

	new_timestamp = get_timestamp(starting_time);
	time_diff = new_timestamp - timestamp;
	return (time_diff);
}

long	oversleep_is_for_the_weak(long starting_time, long timestamp, long sleep_time)
{
	long	time_diff;

	if (sleep_time > 100)
		usleep(sleep_time * 955);
	else
		usleep(sleep_time * 500);
	time_diff = get_time_diff(starting_time, timestamp);
	while (time_diff < sleep_time)
		time_diff = get_time_diff(starting_time, timestamp);
	return (timestamp + time_diff);
}
