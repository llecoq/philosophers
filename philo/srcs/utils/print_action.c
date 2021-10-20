/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:29:01 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/20 17:21:02 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	print_action(t_philosopher *philosopher, int philosopher_nb, int action)
{
	char	*str;
	long	timestamp;

	pthread_mutex_lock(&philosopher->parameters->print_action);
	str = NULL;
	timestamp = get_timestamp(philosopher->parameters);
	philosopher->last_action_time = timestamp;
	if (philosopher->parameters->status == DEAD)
		return ;
	if (action == HAS_TAKEN_A_FORK)
	{
		str = WHITE"has taken a fork"RESET;
		// philosopher->
	}
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
	{
		philosopher->parameters->status = DEAD;
		str = RED"died"RESET;
	}
	printf("%05ld\t%-5d %s\n", timestamp, philosopher_nb, str);
	pthread_mutex_unlock(&philosopher->parameters->print_action);
}
