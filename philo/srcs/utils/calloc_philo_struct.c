/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_philo_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:13:21 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/14 14:14:22 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

// int	calloc_philosopher_struct(t_parameters *params)
// {
// 	int	nb_of_philosophers;
// 	int	i;

// 	nb_of_philosophers = params->nb_of_philosophers + 1;
// 	params->philosopher = malloc(nb_of_philosophers * sizeof(t_philosopher *));
// 	if (params->philosopher == NULL)
// 		return (error(SYSCALL_ERROR, NULL));
// 	i = -1;
// 	while (++i < nb_of_philosophers)
// 	{
// 		params->philosopher[i] = malloc(sizeof(t_philosopher));
// 		if (params->philosopher[i] == NULL)
// 			return (error_clear(params, SYSCALL_ERROR, NULL));
// 	// dprintf(2, "i = %d\tp = %p\n", i, params->philosopher[i]);
// 	}
// 	params->philosopher[--i] = NULL;
// 	return (IS_VALID);
// }
