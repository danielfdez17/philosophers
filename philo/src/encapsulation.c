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

void	set_bool(t_mutex *mtx, bool *dest, bool value)
{
	safe_mutex_handler(mtx, LOCK);
	*dest = value;
	safe_mutex_handler(mtx, UNLOCK);
}

bool	get_bool(t_mutex *mtx, bool *value)
{
	bool	ret;

	safe_mutex_handler(mtx, LOCK);
	ret = *value;
	safe_mutex_handler(mtx, UNLOCK);
	return (ret);
}

void	set_long(t_mutex *mtx, long *dest, long value)
{
	safe_mutex_handler(mtx, LOCK);
	*dest = value;
	safe_mutex_handler(mtx, UNLOCK);
}

long	get_long(t_mutex *mtx, long *value)
{
	long	ret;

	safe_mutex_handler(mtx, LOCK);
	ret = *value;
	safe_mutex_handler(mtx, UNLOCK);
	return (ret);
}

bool	is_dinner_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_dinner));
}
