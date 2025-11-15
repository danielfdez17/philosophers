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
	(void)philosopher;
	// printf("%ld %d %s %ld\n", tv.tv_usec, philosopher.id, get_status_msg(philosopher.status), philosopher.curr_ttdie);
	printf("%ld %d %s\n", tv.tv_usec, philosopher.id, get_status_msg(philosopher.status));
}

void	philo_eat(t_philosopher *philosopher)
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
			else if (philosopher->right)
				print_status(*philosopher);
		}

	}
	philosopher->status = EATING;
	usleep(philosopher->time_to_eat);
	philosopher->n_eat--;
	print_status(*philosopher);

	philosopher->curr_ttdie -= philosopher->time_to_eat;
	if (philosopher->curr_ttdie <= 0)
	{
		philosopher->status = DEAD;
		print_status(*philosopher);
	}
	else
		philosopher->curr_ttdie = philosopher->time_to_die;
	if (philosopher->right)
		pthread_mutex_unlock(philosopher->right);
	pthread_mutex_unlock(philosopher->left);
}

void	philo_sleep(t_philosopher *philosopher)
{
	philosopher->status = SLEEPING;
	print_status(*philosopher);
	philosopher->curr_ttdie -= philosopher->time_to_sleep;
	usleep(philosopher->time_to_sleep);
	if (philosopher->curr_ttdie <= 0)
	{
		philosopher->status = DEAD;
		print_status(*philosopher);
	}
}

void	update_philo_status(t_philosopher *philosopher)
{
	if (philosopher->curr_ttdie <= 0)
	{
		philosopher->status = DEAD;
		print_status(*philosopher);
	}
	else if (philosopher->status == FORK_TAKEN)
		philo_eat(philosopher);
	else if (philosopher->status == EATING)
		philo_sleep(philosopher);
	else if (philosopher->status == SLEEPING)
	{
		philosopher->status = THINKING;
		print_status(*philosopher);
	}
	else if (philosopher->status == THINKING)
		philosopher->status = FORK_TAKEN;
		// update_philo_status(philosopher, time_to_die);
	// sleep(1);
}