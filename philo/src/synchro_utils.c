/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Waits until all philosopher threads are ready.
 */
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_threads_ready))
		;
}

/**
 * Checks if all philosopher threads are running.
 */
bool	are_all_threads_running(t_mutex *mutex, long *threads, long n_philos)
{
	bool	ret;

	safe_mutex_handler(mutex, LOCK);
	ret = (*threads == n_philos);
	safe_mutex_handler(mutex, UNLOCK);
	return (ret);
}

/**
 * Increases a long @param value in a thread-safe manner.
 */
void	increase_long(t_mutex *mutex, long *value)
{
	safe_mutex_handler(mutex, LOCK);
	(*value)++;
	safe_mutex_handler(mutex, UNLOCK);
}

/**
 * De-synchronizes philosophers to prevent deadlocks.
 */
void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->n_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
		return ;
	}
	if (philo->id % 2 == 0)
		think(philo, true);
}
