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

# ifndef MILISECONDS
#  define MILISECONDS 1e3
# endif

# ifndef MICROSECONDS
#  define MICROSECONDS 1e6
# endif

# ifndef NANOSECONDS
#  define NANOSECONDS 1e9
# endif

typedef pthread_mutex_t	t_mutex;

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
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_time_code;

typedef struct s_philo
{
	int				id;
	long			n_eat;
	bool			is_full;
	long			last_meal_time;
	t_mutex			*left;
	t_mutex			*right;
	pthread_t		thread;
	t_mutex			philo_mtx;
	t_table			*table;
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
	long			n_threads_running;
	pthread_t		monitor;
	t_mutex			table_mtx;
	t_mutex			print_mtx;
	t_mutex			*forks;
	t_philo			*philos;
}	t_table;

// * STATUS
void	print_status(t_philo *philo, t_philo_status status);

// * INITIALIZATION
void	init_table(t_table *table);

// * SAFE FUNCTIONS
void	*safe_malloc(size_t bytes);
void	safe_thread_handler(pthread_t *thread, void *(*f)(void *),
			void *data, t_opcode opcode);
void	safe_mutex_handler(t_mutex *mutex, t_opcode opcode);

// * PARSER
void	parse_input(t_table *table, char **av);

// * UTILS
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	error_exit(const char *error);
void	free_table(t_table *table);

// * ENCAPSULATION
void	set_bool(t_mutex *mtx, bool *dest, bool value);
bool	get_bool(t_mutex *mtx, bool *value);
void	set_long(t_mutex *mtx, long *dest, long value);
long	get_long(t_mutex *mtx, long *value);
bool	is_dinner_finished(t_table *table);

// * SYNCHRO UTILS
void	wait_all_threads(t_table *table);
bool	are_all_threads_running(t_mutex *mutex, long *threads, long n_philos);
void	increase_long(t_mutex *mutex, long *value);

// * START
void	start_dinner(t_table *table);
void	think(t_philo *philo, bool pre_simulation);
void	de_synchronize_philos(t_philo *philo);

// * MONITORING
void	*monitor_dinner(void *arg);

#endif // PHILO_H