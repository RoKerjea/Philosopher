/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philomain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:33:18 by rokerjea          #+#    #+#             */
/*   Updated: 2022/05/13 14:33:20 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*
void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	messagefork1;
	pthread_mutex_unlock(&philo->table->print);
	pthread_mutex_lock(&philo->table->print);
	messagefork2;
	messagestarteating;
	pthread_mutex_unlock(&philo->table->print);

	//timestamp_long_long(philo->lastmeal_time)
	usleep(philo->table->philo_meal);

	pthread_mutex_lock(&philo->table->print);
	releasefork2;
	releasefork1;
	pthread_mutex_unlock(&philo->table->print);
}

int	philo_sleep(t_philo *philo)
{
	if (checkifsleepdeath)
		return (0);
	pthread_mutex_lock(&philo->table->print);
	//print message sleep
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->table->philo_sleep);
	pthread_mutex_lock(&philo->table->print);
	//print message think
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}
*/

int	check_last_meal_time(t_philo *philo)
{
	struct timeval *now;
	gettimeofday(&now, 0);
	//transform in long long before comparaison with last_meal_time;
	if (now - last >= philo_life)
	{
		death;
		return (-1);
	}
	return (1);
}

int	stop_condition(t_philo *philo)
{
	if (&philo->table->death == 1)
		return (-1);
	if (check_last_meal_time(philo) == -1)
	{
		pthread_mutex_lock(&philo->table->print);
		printf ("philo n%d died\n", philo->philo_number);
		pthread_mutex_unlock(&philo->table->print);
		pthread_mutex_lock(&philo->table->death);
		philo->table->death = 1;
		pthread_mutex_unlock(&philo->table->death);
		return (-1);
	}
	return (1);
}

void	testparam(t_table *table)
{
	printf("number of philo = %d\n", table->philo_count);
	printf("lifetime = %d\n", table->philo_life);
	printf("mealspeed = %d\n", table->philo_meal);
	printf("sleep time = %d\n", table->philo_sleep);
	printf("max meal = %d\n", table->philo_max_meal);

	return ;
}

void	*ft_start_thread(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	pthread_mutex_lock(philo->table->print);
	printf ("this is philo n%d\n", philo->philo_number);
	pthread_mutex_unlock(philo->table->print);
	while(stop_condition(philo) == 1)
	{
		if (stop_condition == 1)
			philo_eat();
		if (stop_condition == 1)
			philo_sleep();
		if (stop_condition == 1)
			philo_think();
	}
	return ;
}

int	create_start_philo(t_table *table)
{
	printf("gate 6\n");
	int	i;

	i = 0;
	table->philo_list = malloc(sizeof(t_philo) * (table->philo_count + 1));
	if (table->philo_life == 0)
		return(-1);
	while (i < table->philo_count)
	{
		table->philo_list[i].left_fork = table->forks[i];
		if (i + 1 > table->philo_count)
			table->philo_list[i].right_fork = table->forks[0];
		else
			table->philo_list[i].right_fork = table->forks[i + 1];
		table->philo_list[i].philo_number = i + 1;
		if (pthread_create(&table->philo_list[i].thread_id, NULL, ft_start_thread, &table->philo_list[i]) != 0)
			return (-1);
		printf("philo %d created\n", i + 1);
		i++;
	}
	printf("gate 7\n");
	return (1);
}

int	main(int argc, char **argv)
{
	int i;

	i = 0;
	t_table table;
	if (argc < 5 || argc > 6)
		return (0);
	printf("gate 3\n");
	if (parameter_table(argc, argv, &table) == -1)
		return (0);
	printf("gate 4\n");
	while (i < table.philo_count)
	{
		pthread_mutex_init(table.forks[i], 0);
		i++;
	}
	printf("gate 5\n");
	testparam(&table);
	if (create_start_philo(&table) == -1)
		return (0);
	//i = 0;
	/*while (i < table.philo_count)
	{
		pthread_join(table.philo_list[i].thread_id, 0);
		i++;
	}*/
	return (0);
}
/*TO_DO
elements of routine
timestamp converted to long long
death check and write with mutex

*/