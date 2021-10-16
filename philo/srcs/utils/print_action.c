/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:29:01 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/16 11:46:09 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	print_action(long timestamp, int philosopher_nb, int action)
{
	char	*str;

	str = NULL;
	if (action == HAS_TAKEN_A_FORK)
		str = WHITE"has taken a fork"RESET;
	else if (action == IS_EATING)
		str = GREEN"is eating"RESET;
	else if (action == IS_SLEEPING)
		str = MAGENTA"is sleeping"RESET;
	else if (action == IS_THINKING)
		str = CYAN"is thinking"RESET;
	else if (action == DIED)
		str = RED"died"RESET;
	printf("%05ld\t%-5d %s\n", timestamp, philosopher_nb, str);
}
