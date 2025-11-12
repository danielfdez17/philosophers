#include "../inc/philo.h"

void	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->n_philosophers)
	{
		pthread_join(*philo->philosophers[i].thread, NULL);
		++i;
	}
}

void	*philosopher_start(void *arg)
{
	t_philosopher	*philo;
	long		time_to_die;

	philo = (t_philosopher *)arg;
	time_to_die = philo->time_to_die;
	while (philo->status != DEAD || philo->n_eat-- > 0)
		update_philo_status(philo, &time_to_die);
	return (NULL);
}

// ! SO: VC -> variable de condicion
int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ac > 6)
	{
		printf("Needed between 4 and 5 args\n");
		return (0);
	}
	philo = init_philo(ac, av);
	if (!philo)
	{
		printf("An error occurred when initializing t_philo\n");
		return (0);
	}
	join_threads(philo);
	free_philo(&philo);
	return (0);
}
