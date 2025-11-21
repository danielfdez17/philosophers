#include "../inc/philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_threads_ready))
		;
}

bool	all_threads_running(t_mutex *mutex, long *threads, long n_philos)
{
	bool	ret;

	safe_mutex_handler(mutex, LOCK);
	ret = (*threads == n_philos);
	safe_mutex_handler(mutex, UNLOCK);
	return (ret);
}

void	increase_long(t_mutex *mutex, long *value)
{
	safe_mutex_handler(mutex, LOCK);
	(*value)++;
	safe_mutex_handler(mutex, UNLOCK);
}

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
