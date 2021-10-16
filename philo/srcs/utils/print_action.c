/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:29:01 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/16 19:56:34 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

// long	get_timestamp(t_parameters *parameters, long starting_time)
// {
// 	struct timeval	time;
// 	long			timestamp;

// 		if (gettimeofday(&time, NULL) == -1)
// 			return -1; // zob erreur
// 		timestamp = (time.tv_sec * 1000000 + time.tv_usec) * 0.001 - starting_time;
// 		parameters->timestamp = timestamp;
// 	return (timestamp);
// }

void	print_action(t_philosopher *philosopher, int philosopher_nb, int action)
{
	char	*str;
	long	timestamp;

	if (philosopher->parameters->status == DEAD)
		return ;
	timestamp = philosopher->parameters->timestamp;
	philosopher->timestamp = timestamp;
	str = NULL;
	if (action == HAS_TAKEN_A_FORK)
		str = WHITE"has taken a fork"RESET;
	else if (action == IS_EATING)
	{
		philosopher->last_meal_time = timestamp;
		str = GREEN"is eating"RESET;
	}
	else if (action == IS_SLEEPING)
		str = MAGENTA"is sleeping"RESET;
	else if (action == IS_THINKING)
		str = CYAN"is thinking"RESET;
	else if (action == DIED)
		str = RED"died"RESET;
	// timestamp = get_timestamp(parameters, parameters->starting_time);
	printf("%05ld\t%-5d %s\n", timestamp, philosopher_nb - 1, str);
}
