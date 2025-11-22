#include "../inc/philo_bonus.h"

/**
 * Introduces a delay for philosophers with odd IDs in odd-numbered groups
 * to reduce contention for forks.
 */
void	think(t_philo *philo, bool pre_simulation)
{
	long	tteat;
	long	ttsleep;
	long	ttthink;

	if (!pre_simulation)
		print_status(philo, THINKING);
	if (philo->table->n_philos % 2 == 0)
		return ;
	tteat = philo->table->time_to_eat;
	ttsleep = philo->table->time_to_sleep;
	ttthink = tteat * 2 - ttsleep;
	if (ttthink < 0)
		ttthink = 0;
	precise_usleep(ttthink * 0.42, philo->table);
}

/**
 * Handles the case where there is only one philosopher.
 * The philosopher picks up a fork and waits until the dinner ends.
 */
void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_processes(philo->table);
	set_long(philo->philo_sem, &philo->last_meal_time, get_time(MILISECOND));
	increase_long(philo->table->table_sem, &philo->table->n_processes_running);
	print_status(philo, FORK_TAKEN);
	while (!is_dinner_finished(philo->table))
		usleep(200);
	return (NULL);
}

/**
 * Simulates the eating action of a @param philo.
 * The philosopher picks up both forks, eats, and then puts down the forks.
 */
static void	eat(t_philo *philo)
{
	safe_sem_handler(philo->table->forks, WAIT);
	print_status(philo, FORK_TAKEN);
	safe_sem_handler(philo->table->forks, WAIT);
	print_status(philo, FORK_TAKEN);
	set_long(philo->philo_sem, &philo->last_meal_time, get_time(MILISECOND));
	philo->n_eat++;
	print_status(philo, EATING);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->n_eat_per_philosopher > 0
		&& philo->n_eat == philo->table->n_eat_per_philosopher)
		set_bool(philo->philo_sem, &philo->is_full, true);
	safe_sem_handler(philo->table->forks, POST);
	safe_sem_handler(philo->table->forks, POST);
}

/**
 * Main dinner routine for each philosopher.
 * Philosophers wait for all threads to be ready, then enter a loop of eating,
 * sleeping, and thinking until the dinner ends or they are full.
 */
void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_processes(philo->table);
	set_long(philo->philo_sem, &philo->last_meal_time, get_time(MILISECOND));
	increase_long(philo->table->table_sem, &philo->table->n_processes_running);
	de_synchronize_philos(philo);
	while (!is_dinner_finished(philo->table))
	{
		if (philo->is_full)
			break ;
		eat(philo);
		print_status(philo, SLEEPING);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		think(philo, false);
	}
	return (NULL);
}

/**
 * Starts the dinner simulation by creating philosopher threads and the monitor
 * thread. It waits for all philosopher threads to finish before ending
 * the dinner.
 */
void	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->n_eat_per_philosopher == 0)
		return ;
	if (table->n_philos == 1)
		safe_process_handler(&table->philos[0].pid, FORK);
	else
	{
		while (++i < table->n_philos)
			safe_process_handler(&table->philos[i].pid, FORK);
	}
	safe_thread_handler(&table->monitor, monitor_dinner, table, CREATE);
	table->start_time = get_time(MILISECOND);
	set_bool(table->table_sem, &table->all_processes_ready, true);
	i = -1;
	while (++i < table->n_philos)
		safe_process_handler(&table->philos[i].pid, WAIT);
	set_bool(table->table_sem, &table->end_dinner, true);
	safe_thread_handler(&table->monitor, NULL, NULL, JOIN);
}
