/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:22:24 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/17 13:07:37 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	set_starting_time(t_parameters *parameters)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		return ; // zob erreur
	parameters->starting_time = (time.tv_sec * 1000000 + time.tv_usec) * 0.001;
}

void	run_timestamp(t_parameters *parameters)
{
	struct timeval	time;
	long			starting_time;

	starting_time = parameters->starting_time;
	while (1)
	{
		if (gettimeofday(&time, NULL) == -1)
			return ; // zob erreur
		parameters->timestamp
			= (time.tv_sec * 1000000 + time.tv_usec) * 0.001 - starting_time;
		usleep(100);
	}
}
