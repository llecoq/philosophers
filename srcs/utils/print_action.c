/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:29:01 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/21 15:06:20 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

char	*format_string(t_philosopher *philo, int timestamp, int action)
{
	char	*str;

	str = NULL;
	if (action == HAS_TAKEN_A_FORK)
		str = WHITE"has taken a fork"RESET;
	else if (action == IS_EATING)
	{
		philo->last_meal_time = timestamp;
		str = GREEN"is eating"RESET;
	}
	else if (action == IS_SLEEPING)
		str = MAGENTA"is sleeping"RESET;
	else if (action == IS_THINKING)
		str = CYAN"is thinking"RESET;
	else if (action == DIED)
	{
		philo->parameters->status = DEAD;
		str = RED"died"RESET;
	}
	return (str);
}

void	print_action(t_philosopher *philo, int philosopher_nb, int action)
{
	char	*str;
	long	timestamp;

	str = NULL;
	if (pthread_mutex_lock(&philo->parameters->print_action_mutex) >= FAILED)
		return ;
	timestamp = get_timestamp(philo->parameters);
	if (timestamp == -1)
		return ;
	philo->last_action_time = timestamp;
	if (philo->parameters->status == DEAD)
		return ;
	str = format_string(philo, timestamp, action);
	printf("%05ld\t%-5d %s\n", timestamp, philosopher_nb, str);
	if (action != DEAD)
		pthread_mutex_unlock(&philo->parameters->print_action_mutex);
}
