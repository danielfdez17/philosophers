#include "../inc/philo_bonus.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		error_exit("Needes between 4 and 5 args");
	parse_input(&table, av);
	init_table(&table);
	start_dinner(&table);
	free_table(&table);
	return (0);
}