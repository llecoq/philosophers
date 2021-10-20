/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:59:21 by llecoq            #+#    #+#             */
/*   Updated: 2021/10/20 18:03:14 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/errno.h>

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
	SYSCALL_ERROR = 0,
	PARSING_ERROR = 1,
	EXECUTION_ERROR = 2,
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

typedef struct s_parameters
{
	pthread_mutex_t	print_action;
	pthread_mutex_t	had_a_meal;
	int				nb_of_philosophers;
	int				nb_of_philosophers_done_eating;
	int				status;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_meals;
	long			starting_time;
}					t_parameters;

typedef struct s_philosopher
{
	pthread_t		id;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	t_parameters	*parameters;
	int				philosopher_nb;
	int				philosopher_status;
	int				nb_of_meals_to_eat;
	int				nb_of_forks;
	long			last_meal_time;
	long			last_action_time;
}					t_philosopher;

/* ------------------EXECUTION------------------ */
int		execution(t_parameters *parameters);
void	philo_sleep(t_philosopher *philosopher);
void	philo_eat(t_philosopher *philosopher);

/* -------------------PARSING------------------- */

int		parse(t_parameters *parameters, int argc, char **argv);

/* --------------------UTILS-------------------- */

int		error(int error_type, char *arg);
int		error_clear(t_parameters *parameters, int error_type, char *str);
int		clear_memory(t_parameters *parameters, int error_type);
int		calloc_philosopher_struct(t_parameters *parameters);
long	ft_atoi(const char *str);
long	get_timestamp(t_parameters *parameters);
void	oversleep_is_for_the_weak(t_philosopher *philosopher, long sleep_time);
void	print_action(t_philosopher *philosopher, int philosopher_nb, int action);
void	set_starting_time(t_parameters *parameters);
void	life_vs_death_monitor(t_philosopher *philosopher);


#endif