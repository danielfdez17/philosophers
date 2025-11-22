#include "../inc/philo_bonus.h"

/**
 * Waits until all philosopher processes are ready.
 */
void	wait_all_processes(t_table *table)
{
	while (!get_bool(table->table_sem, &table->all_processes_ready))
		;
}

/**
 * Checks if all philosopher processes are running.
 */
bool	are_all_processes_running(t_sem *sem, long *processes, long n_philos)
{
	bool	ret;

	safe_sem_handler(sem, WAIT);
	ret = (*processes == n_philos);
	safe_sem_handler(sem, POST);
	return (ret);
}

/**
 * Increases a long @param value in a thread-safe manner.
 */
void	increase_long(t_sem *sem, long *value)
{
	safe_sem_handler(sem, WAIT);
	(*value)++;
	safe_sem_handler(sem, POST);
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
