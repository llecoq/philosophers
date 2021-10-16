/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:26:16 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/14 14:25:18 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	error(int error_type, char *arg)
{
	printf(BOLDRED"Error: "RESET);
	if (error_type == IS_NOT_A_DIGIT)
		printf("%s is not a digit. The philosopher can see past the concept of\
 the number, but the machine cannot.\n", arg);
	else if (error_type == IS_NEGATIVE)
		printf("[%s] has a negative value. Try to see life in a more positive\
 way.\n",
 arg);
 	else if (error_type == NO_PHILOSOPHER)
	 	printf("\t\t'I think, therefore I am'\tBut does one can think if one\
 does not exist ?\n");
	else if (error_type == TOO_MANY_PHILOSOPHERS)
		printf("Too many philosophers. Calm down Satan.\n");
	else if (error_type == SYSCALL_ERROR)
	{
		printf("Cannot allocate memory\n");
		error_type = FAILED;
	}
	return (error_type);
}

int	error_clear(t_parameters *parameters, int error_type, char *str)
{
	(void)str;
	printf(BOLDRED"Error: "RESET);
	if (error_type == SYSCALL_ERROR)
	{
		printf("Cannot allocate memory\n");   // a voir si autre syscall error
		return (clear_memory(parameters, errno));
	}
	else if (error_type == TOO_FEW_ARGS)
		printf("too few arguments in the parameters. One can argue that size does\
 not matter, but quantity does. Sometimes.\n");
	else if (error_type == TOO_MANY_ARGS)
		printf("too many arguments in the parameters. Less is more.\n");
	printf(BOLDWHITE"Usage: "RESET);
	printf("./philo number_of_philosophers time_to_die time_to_eat\
 time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (clear_memory(parameters, error_type));
}
