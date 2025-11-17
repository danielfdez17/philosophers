#include "../inc/philo.h"

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	safe_mutex_handler(mtx, LOCK);
	*dest = value;
	safe_mutex_handler(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	safe_mutex_handler(mtx, LOCK);
	ret = *value;
	safe_mutex_handler(mtx, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mtx, long *dest, long value)
{
	safe_mutex_handler(mtx, LOCK);
	*dest = value;
	safe_mutex_handler(mtx, UNLOCK);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	safe_mutex_handler(mtx, LOCK);
	ret = *value;
	safe_mutex_handler(mtx, UNLOCK);
	return (ret);
}

bool	is_dinner_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_dinner));
}
