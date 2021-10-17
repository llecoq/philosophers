/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:24 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/17 17:54:13 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	set_starting_time(t_parameters *parameters, long *starting_time)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		return ; // zob erreur
	parameters->starting_time = (time.tv_sec * 1000000 + time.tv_usec) * 0.001;
	*starting_time = parameters->starting_time;
}

void	*run_timestamp(void *arg)
{
	struct timeval	time;
	t_parameters	*parameters;
	long			starting_time;

	parameters = (t_parameters *)arg;
	set_starting_time(parameters, &starting_time);
	// starting_time = parameters->starting_time;
	while (1)
	{
		if (gettimeofday(&time, NULL) == -1)
			return (NULL); // zob erreur
		parameters->timestamp
			= (time.tv_sec * 1000000 + time.tv_usec) * 0.001 - starting_time;
		// usleep(100);
	}
	return (NULL);
}
