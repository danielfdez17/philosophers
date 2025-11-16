/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include "colors.h"
// # include <string.h>

# define FORK_TAKEN_MSG "has taken a fork"
# define IS_EATING_MSG "is eating"
# define IS_THINKING_MSG "is thinking"
# define IS_SLEEPING_MSG "is sleeping"
# define DIED_MSG "died"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef THOUSANDS
#  define THOUSANDS 1000
# endif

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef enum e_philo_status
{
	FORK_TAKEN,
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
}	t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECONDS,
	MILISECONDS,
	MICROSECONDS,
}	t_time_code;

typedef struct s_philo
{
	int				id;
	long			n_eat;
	long			last_meal_time;
	t_mtx			*left;
	t_mtx			*right;
	pthread_t		thread;
	t_table			*table;
	bool			is_full;
	t_mtx			philo_mtx;

	// t_philo_status	status;
	// long			curr_ttdie;
	// long			time_to_die;
	// long			time_to_eat;
	// long			time_to_sleep;
}	t_philo;

typedef struct s_table
{
	long			n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_eat_per_philosopher;
	long			start_time;
	bool			end_dinner;
	bool			all_threads_ready;
	t_mtx			*forks;
	t_mtx			table_mtx;
	t_mtx			print_mtx;
	pthread_t		monitor;
	long			n_threads_running;
	t_philo			*philos;
	
}	t_table;

// * STATUS
void	print_status(t_philo *philo, t_philo_status status);
// void	update_philo_status(t_philo *philosopher);

// * INITIALIZATION
void	init_table(t_table *table);
// t_bool	init_philosophers(t_table *philo);
// t_bool	init_forks(t_table *philo);
// t_table	*init_philo(int ac, char **av);
// * SAFE FUNCTIONS
void	*safe_malloc(size_t bytes);
void	safe_thread_handler(pthread_t *thread, void *(*f)(void *), void *data, t_opcode opcode);
void	safe_mutex_handler(t_mtx *mutex, t_opcode opcode);

// * PARSER
void	parse_input(t_table *table, char **av);

// * UTILS
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	error_exit(const char *error);
// long	ft_atol(char *s);
void	free_table(t_table *table);
// t_bool	check_valid_args(int ac, t_table philo);

// * ENCAPSULATION
void	set_bool(t_mtx *mtx, bool *dest, bool value);
bool	get_bool(t_mtx *mtx, bool *value);
void	set_long(t_mtx *mtx, long *dest, long value);
long	get_long(t_mtx *mtx, long *value);
bool	is_dinner_finished(t_table *table);

// * SYNCHRO UTILS
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long n_philos);
void	increase_long(t_mtx *mutex, long *value);

// * START
void	start_dinner(t_table *table);
void	think(t_philo *philo, bool pre_simulation);
void	de_synchronize_philos(t_philo *philo);
// void	*philosopher_eat_times(void *arg);

// * MONITORING
void	*monitor_dinner(void *arg);

// * ACTIONS
// void	philo_eat(t_philo *philosopher);
// void	philo_sleep(t_philo *philosopher);
// void	philo_dead(t_philo *philosopher);
// void	philo_think(t_philo *philosopher);

#endif // PHILO_H