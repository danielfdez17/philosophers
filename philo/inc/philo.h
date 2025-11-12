#ifndef PHILO_H
#define PHILO_H

#include <string.h>	  // memset
#include <stdio.h>	  // printf
#include <stdlib.h>	  // malloc, free
#include <unistd.h>	  // usleep
#include <sys/time.h> // gettimeofday
#include <pthread.h>  // pthread_*
#include <errno.h>  // pthread_*

#define FORK_TAKEN_MSG "has taken a fork"
#define IS_EATING_MSG "is eating"
#define IS_THINKING_MSG "is thinking"
#define IS_SLEEPING_MSG "is sleeping"
#define DIED_MSG "died"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef	short int	t_bool;

typedef enum e_philo_status
{
	FORK_TAKEN = 0,
	EATING = 1,
	THINKING = 2,
	SLEEPING = 3,
	DEAD = 4,
}	t_philo_status;

typedef enum e_fork_status
{
	FREE = 0,
	TAKEN = 1,
}	t_fork_status;

typedef struct s_philosopher
{
	int				id;
	t_philo_status	status;
	pthread_t		*thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_eat;
}	t_philosopher;

typedef struct s_fork
{
	int 			id;
	t_fork_status	status;
	pthread_mutex_t	*mutex;
}	t_fork;

typedef struct s_philo
{
	long			n_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_eat_per_philosopher;
	t_philosopher	*philosophers;
	t_fork 			*forks;
}	t_philo;

// * STATUS
void	print_status(t_philosopher philosopher);
void	update_philo_status(t_philosopher *philosopher, long *time_to_die);

// * INITIALIZATION
t_bool	init_philosophers(t_philo *philo);
t_bool	init_forks(t_philo *philo);
t_philo	*init_philo(int ac, char **av);

// * UTILS
long	ft_atol(char *s);
void	*free_philo(t_philo **philo);
t_bool	check_valid_args(int ac, t_philo philo);

// * FORKS

void	*philosopher_start(void *arg);
// TODO: function when last arg is not given


#endif // PHILO_H