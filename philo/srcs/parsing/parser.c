/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:56:50 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/21 15:08:24 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	parameters_are_digit(char **argv)
{
	int	i;
	int	j;
	int	status;

	status = IS_VALID;
	i = -1;
	while (argv[++i])
	{
		j = -1;
		if (argv[i][0] == '+' || argv[i][0] == '-')
			j++;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				error(IS_NOT_A_DIGIT, argv[i]);
				status = PARSING_ERROR;
				break ;
			}
		}
	}
	return (status);
}

int	parameters_are_wrong(t_parameters *parameters, int argc)
{
	int	status;

	status = IS_VALID;
	if (parameters->nb_of_philosophers < 0)
		status = error(IS_NEGATIVE, "nb_of_philosophers");
	else if (parameters->nb_of_philosophers == 0)
		status = error(NO_PHILOSOPHER, NULL);
	if (parameters->time_to_die < 0)
		status = error(IS_NEGATIVE, "time_to_die");
	if (parameters->time_to_eat < 0)
		status = error(IS_NEGATIVE, "time_to_eat");
	if (parameters->time_to_sleep < 0)
		status = error(IS_NEGATIVE, "time_to_sleep");
	if (argc == 6 && parameters->nb_of_meals < 0)
		status = error(IS_NEGATIVE, "nb_of_times_each_philosopher_must_eat");
	if (parameters->nb_of_philosophers > 200)
		status = error(TOO_MANY_PHILOSOPHERS, "nb_of_philosophers");
	return (status);
}

int	parse(t_parameters *parameters, int argc, char **argv)
{
	if (parameters_are_digit(argv) == IS_VALID)
	{
		parameters->nb_of_philosophers = ft_atoi(argv[0]);
		parameters->time_to_die = ft_atoi(argv[1]);
		parameters->time_to_eat = ft_atoi(argv[2]);
		parameters->time_to_sleep = ft_atoi(argv[3]);
		if (argc == 6)
			parameters->nb_of_meals = ft_atoi(argv[4]);
	}
	else
		return (PARSING_ERROR);
	if (parameters_are_wrong(parameters, argc))
		return (PARSING_ERROR);
	return (IS_VALID);
}
