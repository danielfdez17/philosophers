#include "../inc/philo.h"

static bool	is_philo_dead(t_philo *philo)
{
	long	elapsed;
	long	ttdie;

	if (get_bool(&philo->philo_mtx, &philo->is_full))
		return (false);
	elapsed = get_time(MILISECONDS) - get_long(&philo->philo_mtx, &philo->last_meal_time);
	ttdie = philo->table->time_to_die / 1e3;
	return (elapsed > ttdie);
}

void	*monitor_dinner(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!all_threads_running(&table->table_mtx, &table->n_threads_running,
			table->n_philos))
		;
	while (!is_dinner_finished(table))
	{
		i = -1;
		while (++i < table->n_philos && !is_dinner_finished(table))
		{
			if (is_philo_dead(&table->philos[i]))
			{
				set_bool(&table->table_mtx, &table->end_dinner, true);
				print_status(&table->philos[i], DEAD);
			}
		}
	}
	return (NULL);
}
