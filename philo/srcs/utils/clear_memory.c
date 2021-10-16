/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:36:30 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/14 14:17:03 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

// void	clear_tab(t_philosopher ***philosopher)
// {
// 	int	i;

// 	i = -1;
// 	while ((*philosopher)[++i])
// 	{
// 		free((*philosopher)[i]);
// 		(*philosopher)[i] = NULL;
// 	}
// 	free((*philosopher)[i]);
// 	free(*philosopher);
// }

int	clear_memory(t_parameters *parameters, int error_type)
{
	(void)parameters;
	// if (parameters->philosopher)
		// clear_tab(&parameters->philosopher, parameters->nb);	
	return (error_type);
}
