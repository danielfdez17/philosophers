/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofday failed");
	if (time_code == SECOND)
		return (tv.tv_sec + tv.tv_usec / MICROSECONDS);
	if (time_code == MILISECOND)
		return ((tv.tv_sec * MILISECONDS) + (tv.tv_usec / MILISECONDS));
	if (time_code == MICROSECOND)
		return ((tv.tv_sec * MICROSECONDS) + tv.tv_usec);
	error_exit("Wrong input to get_time");
	return (-1);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (is_dinner_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > MILISECONDS) // * miliseconds
			usleep(remaining / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	error_exit(const char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}

void	free_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		safe_mutex_handler(&table->philos[i].philo_mtx, DESTROY);
	safe_mutex_handler(&table->table_mtx, DESTROY);
	safe_mutex_handler(&table->print_mtx, DESTROY);
	free(table->philos);
	free(table->forks);
}
