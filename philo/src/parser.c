/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	else if (s[i++] == '-')
		error_exit("Required only positive values");
	while (s[i] >= '0' && s[i] <= '9')
		result = result * 10 + (s[i++] - '0');
	if (result > INT_MAX)
		error_exit("Required only integer values");
	return (result);
}

void	parse_input(t_table *table, char **av)
{
	table->n_philos = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * THOUSANDS;
	table->time_to_eat = ft_atol(av[3]) * THOUSANDS;
	table->time_to_sleep = ft_atol(av[4]) * THOUSANDS;
	table->n_eat_per_philosopher = -1;
	if (av[5])
		table->n_eat_per_philosopher = ft_atol(av[5]);
}
