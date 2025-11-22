#include "../inc/philo_bonus.h"

/**
 * Gets the current time in the specified unit.
 */
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

/**
 * Sleeps for a precise amount of microseconds, checking periodically
 * if the dinner has finished to exit early if needed.
 */
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
		if (remaining > MILISECONDS)
			usleep(remaining / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

/**
 * Prints an error message and exits the program.
 */
void	error_exit(const char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}

/**
 * Frees all allocated resources in the table structure.
 */
void	free_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		safe_sem_handler(table->philos[i].philo_sem, CLOSE);
	safe_sem_handler(table->table_sem, CLOSE);
	safe_sem_handler(table->print_sem, CLOSE);
	free(table->philos);
	free(table->forks);
}
