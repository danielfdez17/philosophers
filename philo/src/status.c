/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/18 10:25:23 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_philo *philo, t_philo_status status)
{
	long	elapsed;
	bool	finished;

	elapsed = get_time(MILISECONDS);
	finished = is_dinner_finished(philo->table);
	if (philo->is_full)
		return ;
	safe_mutex_handler(&philo->table->print_mtx, LOCK);
	if (status == FORK_TAKEN && !finished)
		printf(WHITE"%-6ld"YELLOW " %d has taken a fork\n"RESET, elapsed, philo->id);
	else if (status == EATING && !finished)
		printf(WHITE"%-6ld"CYAN " %d is eating\n"RESET, elapsed, philo->id);
	else if (status == SLEEPING && !finished)
		printf(WHITE"%-6ld"GREEN " %d is sleeping\n"RESET, elapsed, philo->id);
	else if (status == THINKING && !finished)
		printf(WHITE"%-6ld"MAGENTA " %d is thinking\n"RESET, elapsed, philo->id);
	else if (status == EATING)
		printf(RED"%-6ld %d has taken a fork\n"RESET, elapsed, philo->id);
	safe_mutex_handler(&philo->table->print_mtx, UNLOCK);
}

