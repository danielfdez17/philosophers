/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include "colors_bonus.h"

# ifndef MILISECONDS
#  define MILISECONDS 1e3
# endif

# ifndef MICROSECONDS
#  define MICROSECONDS 1e6
# endif

# ifndef NANOSECONDS
#  define NANOSECONDS 1e9
# endif

# define FORKS_SEM_NAME "/forks_sem"
# define TABLE_SEM_NAME "/table_sem"
# define PRINT_SEM_NAME "/print_sem"
# define PHILO_SEM_NAME "/philo_sem"

typedef sem_t	t_sem;

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
	WAIT,
	POST,
	OPEN,
	CLOSE,
	CREATE,
	JOIN,
	DETACH,
	FORK,
	KILL,
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
	pid_t			pid;
	t_sem			*philo_sem;
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
	bool			all_processes_ready;
	long			n_processes_running;
	pthread_t		monitor;
	t_sem			*table_sem;
	t_sem			*print_sem;
	t_sem			*forks;
	t_philo			*philos;
}	t_table;

// * STATUS
void	print_status(t_philo *philo, t_philo_status status);

// * INITIALIZATION
void	init_table(t_table *table);

// * SAFE FUNCTIONS
void	*safe_malloc(size_t bytes);
sem_t	*safe_sem_open(const char *name, int oflag, mode_t mode,
	unsigned int value);
void	safe_process_handler(pid_t *pid, t_opcode opcode);
void	process_error_handler(int status);
void	sem_error_handler(int status, t_opcode opcode);
void	safe_sem_handler(t_sem *sem, t_opcode opcode);
void	safe_thread_handler(pthread_t *thread, void *(*f)(void *),
			void *data, t_opcode opcode);
// void	safe_mutex_handler(t_mutex *mutex, t_opcode opcode);

// * PARSER
void	parse_input(t_table *table, char **av);

// * UTILS
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	error_exit(const char *error);
void	free_table(t_table *table);

// * ENCAPSULATION
void	set_bool(t_sem *sem, bool *dest, bool value);
bool	get_bool(t_sem *sem, bool *value);
void	set_long(t_sem *sem, long *dest, long value);
long	get_long(t_sem *sem, long *value);
bool	is_dinner_finished(t_table *table);

// * SYNCHRO UTILS
void	wait_all_processes(t_table *table);
bool	are_all_processes_running(t_sem *sem, long *processes, long n_philos);
void	increase_long(t_sem *sem, long *value);

// * START
void	start_dinner(t_table *table);
void	think(t_philo *philo, bool pre_simulation);
void	de_synchronize_philos(t_philo *philo);

// * MONITORING
void	*monitor_dinner(void *arg);

#endif // PHILO_BONUS_H