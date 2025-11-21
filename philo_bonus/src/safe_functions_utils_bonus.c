#include "../inc/philo_bonus.h"

/**
 * Handles process operations safely, exiting on failure.
 */
void	process_error_handler(int status, t_opcode opcode)
{
	if (status >= 0)
		return ;
	if (status == -1)
		error_exit("Error when creating the child process");
	if (status == EAGAIN)
		error_exit("The  caller  is operating under the SCHED_DEADLINE"
				" scheduling policy and does not have the reset-on-fork"
				" flag set.");
	if (status == ENOMEM)
		error_exit("fork() failed to allocate the necessary kernel structures"
				" because memory is tight");
}

/**
 * Handles sem errors and exits with appropriate messages.
 */
void	sem_error_handler(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN && opcode == WAIT)
		error_exit("The operation could not be performed without blocking");
	if (status == EINTR && opcode == WAIT)
		error_exit("The call was interrupted by a signal handler");
	if (status == ETIMEDOUT && opcode == WAIT)
		error_exit("The call timed out before the semaphore could be locked");
	if (status == EOVERFLOW && opcode == POST)
		error_exit("The maximum allowable value for a semaphore would be"
				" exceeded");
	if (status == EINVAL)
		error_exit("sem is not a valid semaphore");
}
