#include "../inc/philo.h"

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
	printf("everything is correct\n");
	// create_threads(philo);
	free_philo(philo);
	return (0);
}
