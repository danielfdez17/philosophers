/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	take_forks(t_philosopher *philosopher)
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
		return ;
	}
	if (pthread_mutex_lock(philosopher->left) == 0)
	{
		print_status(*philosopher);
		if (philosopher->right && pthread_mutex_lock(philosopher->right) != 0)
			pthread_mutex_unlock(philosopher->left);
		else if (philosopher->right)
			print_status(*philosopher);
	}
}

void	philo_eat(t_philosopher *philosopher)
{
	take_forks(philosopher);
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

void	philo_dead(t_philosopher *philosopher)
{
	philosopher->status = DEAD;
	print_status(*philosopher);
}

void	philo_think(t_philosopher *philosopher)
{
	philosopher->status = THINKING;
	print_status(*philosopher);
}
