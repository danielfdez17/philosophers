/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*result;

	result = malloc(bytes);
	if (!result)
		error_exit("Error with the malloc");
	return (result);
}

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

static void	mutex_error_handler(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid");
	if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid");
	if (status == EDEADLK)
		error_exit("A deadlock would occur if the"
			" thread blocked waiting for mutex");
	if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	if (status == ENOMEM)
		error_exit("The process cannot allocate enough"
			" memory to create another mutex");
	if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	safe_mutex_handler(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		mutex_error_handler(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		mutex_error_handler(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		mutex_error_handler(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Mutex operation not supported");
}
