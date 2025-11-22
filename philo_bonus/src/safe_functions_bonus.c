#include "../inc/philo_bonus.h"

/**
 * Allocates memory safely, exiting on failure.
 */
void	*safe_malloc(size_t bytes)
{
	void	*result;

	result = malloc(bytes);
	if (!result)
		error_exit("Error with the malloc");
	return (result);
}

/**
 * Handles mutex operations safely, exiting on failure.
 */
void	safe_process_handler(pid_t *pid, t_opcode opcode)
{
	*pid = fork();
	if (opcode == FORK)
		process_error_handler(*pid);
	else
		error_exit("Process operation not supported");
}

/**
 * Handles sem operations safely, exiting on failure.
 */
void	safe_sem_handler(t_sem *sem, t_opcode opcode)
{
	if (opcode == WAIT)
		sem_error_handler(sem_wait(sem), opcode);
	else if (opcode == POST)
		sem_error_handler(sem_post(sem), opcode);
	else if (opcode == CLOSE)
		sem_error_handler(sem_close(sem), opcode);
	else
		error_exit("Mutex operation not supported");
}

/**
 * Opens a semaphore safely, exiting on failure.
 */
sem_t	*safe_sem_open(const char *name, int oflag, mode_t mode,
	unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, oflag, mode, value);
	if (!sem)
		error_exit("Error when creating semaphore");
	return (sem);
}
