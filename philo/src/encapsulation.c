/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encapsulation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Sets a boolean @param value in a thread-safe manner.
 */
void	set_bool(t_mutex *mtx, bool *dest, bool value)
{
	safe_mutex_handler(mtx, LOCK);
	*dest = value;
	safe_mutex_handler(mtx, UNLOCK);
}

/**
 * Gets a boolean @param value in a thread-safe manner.
 */
bool	get_bool(t_mutex *mtx, bool *value)
{
	bool	ret;

	safe_mutex_handler(mtx, LOCK);
	ret = *value;
	safe_mutex_handler(mtx, UNLOCK);
	return (ret);
}

/**
 * Sets a long @param value in a thread-safe manner.
 */
void	set_long(t_mutex *mtx, long *dest, long value)
{
	safe_mutex_handler(mtx, LOCK);
	*dest = value;
	safe_mutex_handler(mtx, UNLOCK);
}

/**
 * Gets a long @param value in a thread-safe manner.
 */
long	get_long(t_mutex *mtx, long *value)
{
	long	ret;

	safe_mutex_handler(mtx, LOCK);
	ret = *value;
	safe_mutex_handler(mtx, UNLOCK);
	return (ret);
}

/**
 * Checks if the dinner has finished in a thread-safe manner.
 */
bool	is_dinner_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_dinner));
}
