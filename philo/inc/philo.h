#ifndef PHILO_H
#define PHILO_H

#include <string.h>	  // memset
#include <stdio.h>	  // printf
#include <stdlib.h>	  // malloc, free
#include <unistd.h>	  // usleep
#include <sys/time.h> // gettimeofday
#include <pthread.h>  // pthread_*

#define FORK_TAKEN_MSG "has taken a fork"
#define IS_EATING_MSG "is eating"
#define IS_THINKING_MSG "is thinking"
#define IS_SLEEPING_MSG "is sleeping"
#define DIED_MSG "died"

typedef enum e_philo_status
{
	FORK_TAKEN = 0,
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
} t_philo_status;

typedef enum e_fork_status
{
	FREE = 0,
	TAKEN = 1,
} t_fork_status;

typedef struct s_philosopher
{
	int id;
	t_philo_status status;
} t_philosopher;

typedef struct s_fork
{
	int id;
	t_fork_status status;
} t_fork;

typedef struct s_philo
{
	int n_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_spleep;
	int n_eat_per_philosopher;
	t_philosopher *philosophers;
	t_fork *fork;
} t_philo;

void print_status(t_philosopher philosopher);

#endif // PHILO_H