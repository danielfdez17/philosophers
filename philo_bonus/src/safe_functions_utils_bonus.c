#include "../inc/philo_bonus.h"

/**
 * Handles process operations safely, exiting on failure.
 */
void	process_error_handler(int status)
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

/**
 * Handles thread operations safely, exiting on failure.
 */
static void	thread_error_handler(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread");
	if (status == EPERM)
		error_exit("The caller does not hava appropiate permissions");
	if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid");
	if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable");
	if (status == ESRCH)
		error_exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread");
	if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread");
}

/**
 * Handles mutex operations safely, exiting on failure.
 */
void	safe_thread_handler(pthread_t *thread, void *(*f)(void *), void *data,
	t_opcode opcode)
{
	if (opcode == CREATE)
		thread_error_handler(pthread_create(thread, NULL, f, data), opcode);
	else if (opcode == JOIN)
		thread_error_handler(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		thread_error_handler(pthread_detach(*thread), opcode);
	else
		error_exit("Thread operation not supported");
}
