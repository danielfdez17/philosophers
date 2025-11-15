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
	// printf("%ld %d %s\n", tv.tv_usec, philosopher.id,
	// 	get_status_msg(philosopher.status));
}

void	philo_sleep(t_philosopher **philo)
{
	(*philo)->status = SLEEPING;
	(*philo)->curr_ttdie -= (*philo)->time_to_sleep;
	usleep((*philo)->time_to_sleep);
	if ((*philo)->curr_ttdie <= 0)
		(*philo)->status = DEAD;
	print_status(**philo);
}

void	philo_eat(t_philosopher **philo)
{
	if ((*philo)->id % 2 == 0 && (*philo)->right)
	{
		if (pthread_mutex_lock((*philo)->right) == 0)
		{
			print_status(**philo);
			if (pthread_mutex_lock((*philo)->left) != 0)
				pthread_mutex_unlock((*philo)->right);
			else
				print_status(**philo);
		}
	}
	else
	{
		if (pthread_mutex_lock((*philo)->left) == 0)
		{
			print_status(**philo);
			if ((*philo)->right && pthread_mutex_lock((*philo)->right) != 0)
				pthread_mutex_unlock((*philo)->left);
			else
				print_status(**philo);
		}

	}
	(*philo)->status = EATING;
	usleep((*philo)->time_to_eat);
	(*philo)->curr_ttdie -= (*philo)->time_to_eat;
	printf("%d -> ttdie: %ld", (*philo)->id, (*philo)->curr_ttdie);
	if ((*philo)->curr_ttdie <= 0)
	{
		if ((*philo)->right)
		{
			pthread_mutex_unlock((*philo)->right);
			// printf("%d has freed a fork\n", (*philo)->id);
		}
		pthread_mutex_unlock((*philo)->left);
		(*philo)->status = DEAD;
	}
	(*philo)->n_eat--;
	print_status(**philo);
	(*philo)->curr_ttdie = (*philo)->time_to_die;
	if ((*philo)->right)
	{
		pthread_mutex_unlock((*philo)->right);
		// printf("%d has freed a fork\n", (*philo)->id);
	}
	pthread_mutex_unlock((*philo)->left);
	// printf("%d has freed a fork\n", (*philo)->id);
}

void	update_philo_status(t_philosopher **philosopher)
{
	if ((*philosopher)->curr_ttdie <= 0)
	{
		(*philosopher)->status = DEAD;
		print_status(**philosopher);
	}
	else if ((*philosopher)->status == FORK_TAKEN)
		philo_eat(philosopher);
	else if ((*philosopher)->status == EATING)
		philo_sleep(philosopher);
	else if ((*philosopher)->status == SLEEPING)
	{
		(*philosopher)->status = THINKING;
		print_status(**philosopher);
	}
	else if ((*philosopher)->status == THINKING)
		(*philosopher)->status = FORK_TAKEN;
	// sleep(1);
}