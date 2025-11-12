#include "../inc/philo.h"

// ! st
char	*get_status_msg(t_philo_status status)
{
	if (status == FORK_TAKEN)
		return (FORK_TAKEN_MSG);
	if (status == EATING)
		return (IS_EATING_MSG);
	if (status == THINKING)
		return (IS_THINKING_MSG);
	if (status == SLEEPING)
		return (IS_SLEEPING_MSG);
	return (DIED_MSG);
}

void	print_status(t_philosopher philosopher)
{
	struct timeval tv;

	(void)philosopher;
	gettimeofday(&tv, NULL);
	printf("%ld %d %s\n", tv.tv_sec * 1000, philosopher.id, \
		get_status_msg(philosopher.status));
}

void	update_philo_status(t_philosopher *philosopher, long *time_to_die)
{
	if (*time_to_die <= 0)
	{
		philosopher->status = DEAD;
		print_status(*philosopher);
		// printf(" time_to_die: %ld\n", *time_to_die);
	}
	else if (philosopher->status == FORK_TAKEN)
	{
		philosopher->status = EATING;
		pthread_mutex_lock(philosopher->left);
		pthread_mutex_lock(philosopher->right);
		print_status(*philosopher);
		// printf(" time_to_die: %ld\n", *time_to_die);
		usleep(philosopher->time_to_eat);
		philosopher->n_eat--;
		*time_to_die = philosopher->time_to_die;
		pthread_mutex_unlock(philosopher->left);
		pthread_mutex_unlock(philosopher->right);
	}
	else if (philosopher->status == EATING)
	{
		philosopher->status = SLEEPING;
		print_status(*philosopher);
		*time_to_die -= philosopher->time_to_sleep;
		// printf(" time_to_die: %ld\n", *time_to_die);
		usleep(philosopher->time_to_sleep);
	}
	else if (philosopher->status == SLEEPING)
	{
		philosopher->status = THINKING;
		print_status(*philosopher);
		// printf(" time_to_die: %ld\n", *time_to_die);
	}
	else if (philosopher->status == THINKING)
	{
		philosopher->status = FORK_TAKEN;
		print_status(*philosopher);
		// printf(" time_to_die: %ld\n", *time_to_die);
		update_philo_status(philosopher, time_to_die);
	}
	sleep(1);
}