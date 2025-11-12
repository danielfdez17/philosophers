#include "../inc/philo.h"

static char	*get_status_msg(t_philo_status status)
{
	if (status == FORK_TAKEN)
		return (FORK_TAKEN_MSG);
	if (status == EATING)
		return (IS_EATING_MSG);
	if (status == THINKING)
		return (IS_THINKING_MSG);
	if (status == SLEEPING)
		return (IS_SLEEPING_MSG);
	return (DIED_MSG);
}

void	print_status(t_philosopher philosopher)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("%ld %d %s\n", tv.tv_sec * 1000, philosopher.id, \
		get_status_msg(philosopher.status));
}
