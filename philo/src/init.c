#include "../inc/philo.h"

static void	assign_forks(t_philo *philo, t_philosopher **philosopher)
{
	int	i;

	i = (*philosopher)->id - 1;
	if (philo->n_philosophers > 1)
	{
		if (i == 0)
			(*philosopher)->left = philo->forks[philo->n_philosophers - 1].mutex;
		else
			(*philosopher)->left = philo->forks[i - 1].mutex;
		(*philosopher)->right = philo->forks[i].mutex;
	}
	else
	{
		(*philosopher)->left = philo->forks[i].mutex;
		(*philosopher)->right = NULL;
	}
	(*philosopher)->curr_time_to_die = philo->time_to_die;
	(*philosopher)->time_to_die = philo->time_to_die;
	(*philosopher)->time_to_eat = philo->time_to_eat;
	(*philosopher)->time_to_sleep = philo->time_to_sleep;
	(*philosopher)->n_eat = philo->n_eat_per_philosopher;
}

t_bool	init_philosophers(t_philo *philo)
{
	t_philosopher	*philosophers;
	t_philosopher	*aux;
	int	i;

	philosophers = malloc(sizeof(t_philosopher) * philo->n_philosophers);
	if (!philosophers)
		return (FALSE);
	i = 0;
	while (i < philo->n_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].status = SLEEPING;
		philosophers[i].thread = malloc(sizeof(pthread_t));
		if (!philosophers[i].thread)
			return (FALSE);
		if (philo->n_eat_per_philosopher < 0)
		{
			if (pthread_create(philosophers[i].thread, NULL, philosopher_no_eat_times, &philosophers[i]) != 0)
				return (FALSE);
		}
		else
		{
			if (pthread_create(philosophers[i].thread, NULL, philosopher_eat_times, &philosophers[i]) != 0)
				return (FALSE);
		}
		aux = &philosophers[i];
		assign_forks(philo, &aux);
		++i;
	}
	philo->philosophers = philosophers;
	return (TRUE);
}

t_bool	init_forks(t_philo *philo)
{
	t_fork	*forks;
	int	i;

	forks = malloc(sizeof(t_fork) * philo->n_philosophers);
	if (!forks)
		return (FALSE);
	i = 0;
	while (i < philo->n_philosophers)
	{
		forks[i].id = i + 1;
		forks[i].status = FREE;
		forks[i].mutex = malloc(sizeof(pthread_mutex_t));
		if (!forks[i].mutex)
			return (FALSE);
		if (pthread_mutex_init(forks[i].mutex, NULL) != 0)
			return (FALSE);
		++i;
	}
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
		return free_philo(&philo);
	return (philo);
}
