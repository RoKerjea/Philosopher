#include "../include/philosopher.h"

//just need mutex lock for last meal time in case philo start eating when monitor is checking
int	check_last_meal_time(t_philo *philo)
{
	long long	now;
	int res;

	now = runtime(philo);
	res = 1;
	//need mutex_lock() for writing/reading lastmeal time
	if (now - philo->last_meal >= philo->philo_life)
		res = -1;
	//need mutex_unlock() for writing/reading lastmeal time
	return (res);
}

long long	timestamp_ms(void)
{
	struct timeval	time_now;
	long long		res;

	gettimeofday(&time_now, 0);
	res = time_now.tv_sec * 1000 + time_now.tv_usec / 1000;
	return (res);
}

long long	runtime(struct s_philo *philo)
{
	long long	res;

	res = timestamp_ms() - philo->start_time;
	return (res);
}