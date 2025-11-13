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

	gettimeofday(&tv, NULL);
	printf("%ld %d %s %ld\n", tv.tv_sec * 1000, philosopher.id, get_status_msg(philosopher.status), philosopher.n_eat);
	// printf("%ld %d %s\n", tv.tv_sec * 1000, philosopher.id, 
	// 	get_status_msg(philosopher.status));
}

void	update_philo_status(t_philosopher *philosopher)
{
	if (philosopher->curr_time_to_die <= 0)
	{
		philosopher->status = DEAD;
		print_status(*philosopher);

	}
	else if (philosopher->status == FORK_TAKEN)
	{
		if (philosopher->id % 2 == 0 && philosopher->right)
		{
			if (pthread_mutex_lock(philosopher->right) == 0)
			{
				print_status(*philosopher);
				if (pthread_mutex_lock(philosopher->left) != 0)
					pthread_mutex_unlock(philosopher->right);
				else
					print_status(*philosopher);
			}
		}
		else
		{
			if (pthread_mutex_lock(philosopher->left) == 0)
			{
				print_status(*philosopher);
				if (philosopher->right && pthread_mutex_lock(philosopher->right) != 0)
					pthread_mutex_unlock(philosopher->left);
				else
					print_status(*philosopher);
			}

		}
		philosopher->status = EATING;
		usleep(philosopher->time_to_eat * MILISECS);
		philosopher->n_eat--;
		print_status(*philosopher);

		philosopher->curr_time_to_die = philosopher->time_to_die;
		if (philosopher->right)
		{
			pthread_mutex_unlock(philosopher->right);
			printf("%d has freed a fork\n", philosopher->id);
		}
		pthread_mutex_unlock(philosopher->left);
		printf("%d has freed a fork\n", philosopher->id);
	}
	else if (philosopher->status == EATING)
	{
		philosopher->status = SLEEPING;
		philosopher->curr_time_to_die -= philosopher->time_to_sleep;
		print_status(*philosopher);

		usleep(philosopher->time_to_sleep * MILISECS);
	}
	else if (philosopher->status == SLEEPING)
	{
		philosopher->status = THINKING;
		print_status(*philosopher);
	}
	else if (philosopher->status == THINKING)
	{
		philosopher->status = FORK_TAKEN;
		// update_philo_status(philosopher, time_to_die);
	}
	// print_status(*philosopher);
	// printf(" time_to_die: %ld, n_eat: %ld\n", *time_to_die, philosopher->n_eat);
	// sleep(1);
}