/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:24:07 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/21 15:24:35 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define BOLDRED     "\033[1m\033[31m"
# define BOLDGREEN   "\033[1m\033[32m"
# define BOLDCYAN    "\033[1m\033[36m"
# define BOLDWHITE   "\033[1m\033[37m"

enum	e_mutex
{
	CREATE,
	DETACH,
};

enum	e_status
{
	DEAD,
	ALIVE,
	EATING,
	SLEEPING,
	THINKING,
	TIME_TO_DIE,
};

enum	e_erros
{
	NO_ERROR = -2,
	SUCCESS = 0,
	SYSCALL_ERROR = 0,
	PARSING_ERROR = 1,
	EXECUTION_ERROR = 2,
	INITIALIZATION_ERROR = 3,
	TOO_MANY_ARGS = 3,
	TOO_FEW_ARGS = 4,
	IS_NEGATIVE = 5,
	NO_PHILOSOPHER = 6,
	TOO_MANY_PHILOSOPHERS = 7,
	IS_NOT_A_DIGIT = 8,
	FAILED = 1,
	NOT_SET = -1,
	IS_SET = 0,
};

enum	e_actions
{
	EAT,
	SLEEP,
	HAS_TAKEN_A_FORK,
	IS_EATING,
	IS_SLEEPING,
	IS_THINKING,
	DIED,
};

enum	e_digit
{
	IS_VALID = 0,
	IS_DIGIT = 0,
};

#endif