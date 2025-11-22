#include "../inc/philo_bonus.h"

/**
 * Checks if a @param philo is dead based on the time since their last meal.
 */
static bool	is_philo_dead(t_philo *philo)
{
	long	elapsed;
	long	ttdie;

	if (get_bool(philo->philo_sem, &philo->is_full))
		return (false);
	elapsed = get_time(MILISECOND) - get_long(philo->philo_sem,
			&philo->last_meal_time);
	ttdie = philo->table->time_to_die / MILISECONDS;
	return (elapsed > ttdie);
}

/**
 * Monitor thread function that checks the status of philosophers.
 * It ends the dinner if any philosopher dies or if all have eaten enough.
 */
void	*monitor_dinner(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!are_all_processes_running(table->table_sem,
			&table->n_processes_running, table->n_philos))
		;
	while (!is_dinner_finished(table))
	{
		i = -1;
		while (++i < table->n_philos && !is_dinner_finished(table))
		{
			if (is_philo_dead(&table->philos[i]))
			{
				set_bool(table->table_sem, &table->end_dinner, true);
				print_status(&table->philos[i], DEAD);
			}
		}
	}
	return (NULL);
}
