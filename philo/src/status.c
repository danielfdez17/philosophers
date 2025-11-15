/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld %d %s\n", tv.tv_usec, philosopher.id,
		get_status_msg(philosopher.status));
}

void	update_philo_status(t_philosopher *philosopher)
{
	if (philosopher->curr_ttdie <= 0)
		philo_dead(philosopher);
	else if (philosopher->status == FORK_TAKEN)
		philo_eat(philosopher);
	else if (philosopher->status == EATING)
		philo_sleep(philosopher);
	else if (philosopher->status == SLEEPING)
		philo_think(philosopher);
	else if (philosopher->status == THINKING)
		philosopher->status = FORK_TAKEN;
}
