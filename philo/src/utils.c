#include "../inc/philo.h"

long	ft_atol(char *s)
{
	int		i;
	long	result;
	int		negative;

	i = 0;
	result = 0;
	negative = 0;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		++i;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			negative = 1;
	while (s[i] >= '0' && s[i] <= '9')
		result = result * 10 + (s[i++] - '0');
	if (negative)
		return (-result);
	return (result);
}

void	*free_philo(t_philo **philo)
{
	int	i;

	i = 0;
	if (*philo && (*philo)->forks)
	{
		while (i < (*philo)->n_philosophers)
		{
			pthread_mutex_destroy((*philo)->forks[i].mutex);
			free((*philo)->forks[i].mutex);
			(*philo)->forks[i++].mutex = NULL;
		}
		free((*philo)->forks);
		(*philo)->forks = NULL;
	}
	i = 0;
	if (*philo && (*philo)->philosophers)
	{
		while (i < (*philo)->n_philosophers)
		{
			free((*philo)->philosophers[i++].thread);
		}
		free((*philo)->philosophers);
		(*philo)->philosophers = NULL;
	}
	if (*philo)
	{
		free(*philo);
		*philo = NULL;
	}
	return (NULL);
}

t_bool	check_valid_args(int ac, t_philo philo)
{
	if (philo.n_philosophers <= 0)
		return (FALSE);
	if (philo.time_to_die <= 0)
		return (FALSE);
	if (philo.time_to_eat <= 0)
		return (FALSE);
	if (philo.time_to_sleep <= 0)
		return (FALSE);
	if (ac == 6 && philo.n_eat_per_philosopher <= 0)
		return (FALSE);
	return (TRUE);
}
