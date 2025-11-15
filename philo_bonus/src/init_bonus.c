/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	assign_forks(t_philo *philo, t_philosopher **philosopher)
{
	(*philosopher)->forks = philo->forks;
	(*philosopher)->curr_ttdie = philo->time_to_die;
	(*philosopher)->time_to_die = philo->time_to_die;
	(*philosopher)->curr_ttdie = philo->time_to_die;
	(*philosopher)->time_to_eat = philo->time_to_eat;
	(*philosopher)->time_to_sleep = philo->time_to_sleep;
	(*philosopher)->n_eat = philo->n_eat_per_philosopher;
}

t_bool	init_philosophers(t_philo *philo)
{
	t_philosopher	*philosophers;
	t_philosopher	*aux;
	int				i;
	pid_t			pid;

	philosophers = malloc(sizeof(t_philosopher) * philo->n_philosophers);
	if (!philosophers)
		return (FALSE);
	i = 0;
	while (i < philo->n_philosophers)
	{
		pid = fork();
		if (pid < 0)
			return (FALSE);
		if (pid == 0)
			exit(0);
		philosophers[i].id = i + 1;
		philosophers[i].status = SLEEPING;
		philosophers[i].pid = pid;
		aux = &philosophers[i];
		assign_forks(philo, &aux);
		++i;
	}
	philo->philosophers = philosophers;
	return (TRUE);
}

t_bool	init_forks(t_philo *philo)
{
	sem_t	*forks;

	forks = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, philo->n_philosophers);
	if (!forks)
		return (FALSE);
	philo->forks = forks;
	return (TRUE);
}

t_philo	*init_philo(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->n_philosophers = ft_atol(av[1]);
	// TODO: convert to miliseconds
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	philo->n_eat_per_philosopher = -1;
	if (ac == 6)
		philo->n_eat_per_philosopher = ft_atol(av[5]);
	if (!check_valid_args(ac, *philo))
	{
		free(philo);
		return (NULL);
	}
	if (!init_forks(philo) || !init_philosophers(philo))
		return (free_philo(&philo));
	return (philo);
}
