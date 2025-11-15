/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danfern3 <danfern3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:07:54 by danfern3          #+#    #+#             */
/*   Updated: 2025/11/10 12:38:25 by danfern3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ac > 6)
	{
		printf("Needed between 4 and 5 args\n");
		return (0);
	}
	(void)philo;
	(void)av;
	// int size = 5;
	// pid_t	*processes;
	// processes = malloc(sizeof(pid_t) * size);
	// if (!processes)
	// 	return (1);
	// sem_t *sem = sem_open("/philo_forks", O_CREAT, 0644, 5);
	// for (int i = 0; i < 5; ++i)
	// {
	// 	pid_t pid = fork();
	// 	if (pid < 0)
	// 		exit(EXIT_FAILURE);
	// 	if (pid == 0)
	// 		exit(EXIT_SUCCESS);
	// 	if (pid > 0)
	// 	{
	// 		processes[i] = pid;
	// 		printf("Created process with PID: %d\n", pid);
	// 	}
	// }

	// free(processes);
	philo = init_philo(ac, av);
	if (!philo)
	{
		printf("An error occurred when initializing t_philo\n");
		return (0);
	}
	while (wait(NULL) > 0)
		;
	free_philo(&philo);
	return (0);
}
