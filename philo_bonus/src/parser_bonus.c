#include "../inc/philo_bonus.h"

/**
 * Converts a string @param s to a long integer.
 * Exits with an error if the string is not a valid positive integer
 * or if it exceeds INT_MAX.
 */
static long	ft_atol(char *s)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		++i;
	if (s[i] == '+')
		++i;
	else if (s[i] == '-')
		error_exit("Required only positive values");
	while (s[i] >= '0' && s[i] <= '9')
		result = result * 10 + (s[i++] - '0');
	if (result > INT_MAX)
		error_exit("Required only integer values");
	return (result);
}

/**
 * Parses command-line @param av and populates the @param table structure.
 */
void	parse_input(t_table *table, char **av)
{
	table->n_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * MILISECONDS;
	table->time_to_eat = ft_atol(av[3]) * MILISECONDS;
	table->time_to_sleep = ft_atol(av[4]) * MILISECONDS;
	table->n_eat_per_philosopher = -1;
	if (av[5])
		table->n_eat_per_philosopher = ft_atol(av[5]);
}
