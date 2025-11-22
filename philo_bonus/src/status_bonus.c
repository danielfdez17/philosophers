#include "../inc/philo_bonus.h"

/**
 * Prints the current @param status of a @param philo in a thread-safe manner.
 */
void	print_status(t_philo *philo, t_philo_status status)
{
	long	elapsed;
	bool	finished;

	elapsed = get_time(MILISECOND);
	finished = is_dinner_finished(philo->table);
	if (philo->is_full)
		return ;
	safe_sem_handler(philo->table->print_sem, WAIT);
	if (status == FORK_TAKEN && !finished)
		printf(WHITE"%-6ld"YELLOW " %d has taken a fork\n"RESET,
			elapsed, philo->id);
	else if (status == EATING && !finished)
		printf(WHITE"%-6ld"CYAN " %d is eating\n"RESET, elapsed, philo->id);
	else if (status == SLEEPING && !finished)
		printf(WHITE"%-6ld"GREEN " %d is sleeping\n"RESET, elapsed, philo->id);
	else if (status == THINKING && !finished)
		printf(WHITE"%-6ld"MAGENTA " %d is thinking\n"RESET,
			elapsed, philo->id);
	else if (status == DEAD)
		printf(RED"%-6ld %d has died\n"RESET, elapsed, philo->id);
	safe_sem_handler(philo->table->print_sem, POST);
}
