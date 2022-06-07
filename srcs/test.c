#include "../include/philosopher.h"

//Just needed for test, TO_MOVE and DEL
void	testparam(t_table *table)
{
	printf("number of philo = %d\n", table->philo_count);
	printf("lifetime = %d\n", table->philo_life);
	printf("mealspeed = %d\n", table->philo_meal);
	printf("sleep time = %d\n", table->philo_sleep);
	printf("max meal = %d\n", table->philo_max_meal);
	printf("death? = %d\n", table->death);

	return ;
}

void	ft_test_philo_data(t_philo *philo)
{
	printf("number of philo actual = %d\n", philo->philo_number);
	printf("lifetime = %d\n", philo->philo_life);
	printf("mealspeed = %d\n", philo->philo_meal);
	printf("sleep time = %d\n", philo->philo_sleep);
	printf("max meal = %d\n", philo->philo_max_meal);
	return ;
}