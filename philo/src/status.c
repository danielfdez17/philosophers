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
	}
	else if (philosopher->status == FORK_TAKEN)
	{
		pthread_mutex_lock(philosopher->left);
		// if (pthread_mutex_lock(philosopher->left) != 0)
		// 	return ;
		print_status(*philosopher);
		// printf("(left one)\n");
		if (philosopher->right)
		{
			if (pthread_mutex_lock(philosopher->right) != 0)
				pthread_mutex_unlock(philosopher->left);
			print_status(*philosopher);
			// printf("(right one)\n");
		}
		philosopher->status = EATING;
		usleep(philosopher->time_to_eat);
		philosopher->n_eat--;
		*time_to_die = philosopher->time_to_die;
		pthread_mutex_unlock(philosopher->left);
		// printf("\n%d: freed left fork\n", philosopher->id);
		if (philosopher->right)
		{
			pthread_mutex_unlock(philosopher->right);
			// printf("\n%d: freed right fork\n", philosopher->id);
		}
	}
	else if (philosopher->status == EATING)
	{
		philosopher->status = SLEEPING;
		*time_to_die -= philosopher->time_to_sleep;
		usleep(philosopher->time_to_sleep);
	}
	else if (philosopher->status == SLEEPING)
	{
		philosopher->status = THINKING;
	}
	else if (philosopher->status == THINKING)
	{
		philosopher->status = FORK_TAKEN;
		return ;
		// update_philo_status(philosopher, time_to_die);
	}
	print_status(*philosopher);
	// printf(" time_to_die: %ld, n_eat: %ld\n", *time_to_die, philosopher->n_eat);
	// sleep(1);
}