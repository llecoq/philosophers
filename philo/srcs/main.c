/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:01:54 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/20 15:05:15 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_parameters(t_parameters *parameters)
{
	parameters->nb_of_philosophers = 0;
	parameters->status = ALIVE;
	parameters->time_to_die = 0;
	parameters->time_to_eat = 0;
	parameters->time_to_sleep = 0;
	parameters->nb_of_meals = NOT_SET;
	parameters->starting_time = NOT_SET;
	if (pthread_mutex_init(&parameters->print_action, NULL) >= FAILED)
		return ; // ZOB
}

int	main(int argc, char **argv)
{
	t_parameters	parameters;

	if (argc >= 5 && argc <= 6)
	{
		init_parameters(&parameters);
		if (parse(&parameters, argc, ++argv) == PARSING_ERROR)
			return (PARSING_ERROR);
		if (execution(&parameters) == FAILED)
			return (EXECUTION_ERROR);
		clear_memory(&parameters, NO_ERROR);
	}
	if (argc < 5)
		error_clear(&parameters, TOO_FEW_ARGS, NULL);
	else if (argc > 6)
		error_clear(&parameters, TOO_MANY_ARGS, NULL);
	return (EXIT_FAILURE);
}
