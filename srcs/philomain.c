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
int	philo_eat()
{
	messagefork1;
	messagefork2;
	messagestarteating;
	gettimeofday(philo->last_meal_time, 0);
	releasefork2;
	releasefork1;
}

int	philo_sleep()
{
	checkifsleepdeath
	//print message sleep
	usleep(table->philo_sleep);
	//print message think
}

int	stop_condition()
{
	if (last_meal_time - getttimeofday() <= 0)
	{
		//print "timestamp_in_ms X died";
		table->death = 1;
	}
	if (table->death == 1)
		stop thread;
	return (0)
}

int	philoroutine(t_table table, t_philo philo)
{
	while(stop_condition == 0)
	{
		if (stop_condition == 0)
			philo_eat();
		if (stop_condition == 0)
			philo_sleep();
		if (stop_condition == 0)
			philo_think();
	}
}*/

void	testparam(t_table *table)
{
	printf("number of philo = %d\n", table->philo_count);
	printf("lifetime = %d\n", table->philo_life);
	printf("mealspeed = %d\n", table->philo_meal);
	printf("sleep time = %d\n", table->philo_sleep);
	printf("max meal = %d\n", table->philo_max_meal);

	exit(0);
}

void	*ft_start_thread(void *ptr)
{
	t_table *table;

	table = (t_table *) ptr;
	//start routine;
}

int	create_start_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo_list = malloc(sizeof(t_philo) * (table->philo_count + 1));
	if (table->philo_life == NULL)
		return(-1);
	while (i < table->philo_count)
	{
		table->philo_list[i].left_fork = table->forks[i];
		if (i + 1 > table->philo_count)
			table->philo_list[i].right_fork = table->forks[0];
		else
			table->philo_list[i].right_fork = table->forks[i + 1];
		table->philo_list[i].philo_number = i;
		if (pthread_create(table->philo_list[i].thread_id, NULL, ft_start_thread, table) == 0)
			return (-1);
		i++;
	}
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
	while (i < table.philo_count)
	{
		pthread_mutex_init(table.forks[i], 0);
		i++;
	}
	testparam(&table);
	if (create_start_philo(&table) == -1)
		return (0);
	i = 0;
	while (i < table.philo_count)
	{
		pthread_join(table.philo_list[i].thread_id, 0);
		i++;
	}
	return (0);
}
