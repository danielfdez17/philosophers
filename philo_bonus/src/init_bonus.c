#include "../inc/philo_bonus.h"

/**
 * Initializes each philosopher in the dining @param table.
 */
static void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].is_full = false;
		table->philos[i].n_eat = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].pid = fork();
		safe_process_handler(table->philos[i].pid, FORK);
		table->philos[i].philo_sem = safe_sem_open(PHILO_SEM_NAME, O_CREAT, O_RDONLY | O_WRONLY, 1);
	}
}

/**
 * Initializes the dining @param table, philosophers, and forks.
 */
void	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_dinner = false;
	table->all_processes_ready = false;
	table->n_processes_running = 0;
	table->philos = safe_malloc(table->n_philos * sizeof(t_philo));
	table->table_sem = safe_sem_open(TABLE_SEM_NAME, O_CREAT,
		O_RDONLY | O_WRONLY, 1);
	table->print_sem = safe_sem_open(PRINT_SEM_NAME, O_CREAT,
		O_RDONLY | O_WRONLY, 1);
	table->print_sem = safe_sem_open(FORKS_SEM_NAME, O_CREAT,
		O_RDONLY | O_WRONLY, table->n_philos);
	init_philo(table);
}
