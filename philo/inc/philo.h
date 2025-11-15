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

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

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

# ifndef MILISECS
#  define MILISECS 1000
# endif

typedef short int	t_bool;

typedef enum e_philo_status
{
	FORK_TAKEN = 0,
	EATING = 1,
	THINKING = 2,
	SLEEPING = 3,
	DEAD = 4,
}	t_philo_status;

typedef struct s_philosopher
{
	int				id;
	t_philo_status	status;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	long			curr_ttdie;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_eat;
}	t_philosopher;

typedef struct s_philo
{
	long			n_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_eat_per_philosopher;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
}	t_philo;

// * STATUS
void	print_status(t_philosopher philosopher);
void	update_philo_status(t_philosopher *philosopher);

// * INITIALIZATION
t_bool	init_philosophers(t_philo *philo);
t_bool	init_forks(t_philo *philo);
t_philo	*init_philo(int ac, char **av);

// * UTILS
long	ft_atol(char *s);
void	*free_philo(t_philo **philo);
t_bool	check_valid_args(int ac, t_philo philo);

// * FORKS
void	*philosopher_eat_times(void *arg);

#endif // PHILO_H