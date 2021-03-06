/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:24 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/21 15:04:03 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

long	get_timestamp(t_parameters *parameters)
{
	struct timeval	time;
	long			timestamp;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	timestamp = (time.tv_sec * 1000000 + time.tv_usec) * 0.001;
	if (pthread_mutex_lock(&parameters->starting_time_mutex) >= FAILED)
		return (-1);
	timestamp -= parameters->starting_time;
	pthread_mutex_unlock(&parameters->starting_time_mutex);
	return (timestamp);
}

void	set_starting_time(t_parameters *parameters)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return ;
	parameters->starting_time = (time.tv_sec * 1000000 + time.tv_usec) * 0.001;
	if (parameters->nb_of_philosophers <= 10)
		parameters->starting_time += 1000;
	else if (parameters->nb_of_philosophers <= 20)
		parameters->starting_time += 2000;
	else if (parameters->nb_of_philosophers <= 100)
		parameters->starting_time += 3000;
	else if (parameters->nb_of_philosophers <= 200)
		parameters->starting_time += 4000;
	else
		parameters->starting_time += 5000;
	pthread_mutex_unlock(&parameters->starting_time_mutex);
}
