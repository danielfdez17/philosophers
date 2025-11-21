/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->n_threads_running);
	print_status(philo, FORK_TAKEN);
	while (!is_dinner_finished(philo->table))
		usleep(200);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handler(philo->left, LOCK);
	print_status(philo, FORK_TAKEN);
	safe_mutex_handler(philo->right, LOCK);
	print_status(philo, FORK_TAKEN);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILISECOND));
	philo->n_eat++;
	print_status(philo, EATING);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->n_eat_per_philosopher > 0
		&& philo->n_eat == philo->table->n_eat_per_philosopher)
		set_bool(&philo->philo_mtx, &philo->is_full, true);
	safe_mutex_handler(philo->left, UNLOCK);
	safe_mutex_handler(philo->right, UNLOCK);
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->n_threads_running);
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

void	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->n_eat_per_philosopher == 0)
		return ;
	if (table->n_philos == 1)
		safe_thread_handler(&table->philos[0].thread, lone_philo,
			&table->philos[0], CREATE);
	else
	{
		while (++i < table->n_philos)
			safe_thread_handler(&table->philos[i].thread, dinner,
				&table->philos[i], CREATE);
	}
	safe_thread_handler(&table->monitor, monitor_dinner, table, CREATE);
	table->start_time = get_time(MILISECOND);
	set_bool(&table->table_mtx, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->n_philos)
		safe_thread_handler(&table->philos[i].thread, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->end_dinner, true);
	safe_thread_handler(&table->monitor, NULL, NULL, JOIN);
}
