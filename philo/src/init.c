/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	assign_forks(t_philo *philo, t_mtx *forks, int idx)
{
	int	n_philo;

	n_philo = philo->table->n_philos;
	philo->left = &forks[idx];
	philo->right = &forks[(idx + 1) % n_philo];
	if (philo->id % 2 == 0)
	{
		philo->right = &forks[idx];
		philo->left = &forks[(idx + 1) % n_philo];
	}
}

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
		safe_mutex_handler(&table->philos[i].philo_mtx, INIT);
		assign_forks(&table->philos[i], table->forks, i);
	}
}

void	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_dinner = false;
	table->all_threads_ready = false;
	table->n_threads_running = 0;
	table->philos = safe_malloc(table->n_philos * sizeof(t_philo));
	table->forks = safe_malloc(table->n_philos * sizeof(t_mtx));
	safe_mutex_handler(&table->table_mtx, INIT);
	while (++i < table->n_philos)
		safe_mutex_handler(&table->forks[i], INIT);
	init_philo(table);
}
