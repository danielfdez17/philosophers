#include "../inc/philo.h"

void	join_threads(t_philo *philo)
{
	int	i;

	if (!philo)
		return ;
	i = 0;
	while (i < philo->n_philosophers)
	{
		pthread_join(philo->philosophers[i].thread, NULL);
		++i;
	}
}

void	*philosopher_eat_times(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->time_to_die * MILISECS);
	if (philo->n_eat <= 0)
	{
		while (philo->status != DEAD)
		{
			if (philo->curr_ttdie <= 0)
			{
				philo->status = DEAD;
				print_status(*philo);
			}
			update_philo_status(philo);
		}
		return (NULL);
	}
	while (philo->status != DEAD && philo->n_eat > 0)
	{
		if (philo->curr_ttdie <= 0)
		{
			philo->status = DEAD;
			print_status(*philo);
		}
		update_philo_status(philo);
	}
	return (NULL);
}

// void	*philosopher_no_eat_times(void *arg)
// {
// 	t_philosopher	*philo;

// 	philo = (t_philosopher *)arg;
// 	if (philo->id % 2 == 0)
// 		usleep(philo->time_to_die * MILISECS);
// 	while (philo->status != DEAD)
// 	{
// 		if (philo->curr_ttdie <= 0)
// 		{
// 			philo->status = DEAD;
// 			update_philo_status(philo);
// 		}
// 	}
// 	return (NULL);
// }

// ! n_philo, ttdie, tteat, ttsleep n_eat_p_philo
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
