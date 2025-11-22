#include "../inc/philo_bonus.h"

/**
 * Sets a boolean @param value in a process-safe manner.
 */
void	set_bool(t_sem *sem, bool *dest, bool value)
{
	safe_sem_handler(sem, WAIT);
	*dest = value;
	safe_sem_handler(sem, POST);
}

/**
 * Gets a boolean @param value in a process-safe manner.
 */
bool	get_bool(t_sem *sem, bool *value)
{
	bool	ret;

	safe_sem_handler(sem, WAIT);
	ret = *value;
	safe_sem_handler(sem, POST);
	return (ret);
}

/**
 * Sets a long @param value in a process-safe manner.
 */
void	set_long(t_sem *sem, long *dest, long value)
{
	safe_sem_handler(sem, WAIT);
	*dest = value;
	safe_sem_handler(sem, POST);
}

/**
 * Gets a long @param value in a process-safe manner.
 */
long	get_long(t_sem *sem, long *value)
{
	long	ret;

	safe_sem_handler(sem, WAIT);
	ret = *value;
	safe_sem_handler(sem, POST);
	return (ret);
}

/**
 * Checks if the dinner has finished in a process-safe manner.
 */
bool	is_dinner_finished(t_table *table)
{
	return (get_bool(table->table_sem, &table->end_dinner));
}
