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

//make a function for philo parameter before phread_create

void	fork_choice(t_table *table, struct s_philo *philo)
{
	int	num;

	num = philo->num;
	if (num % 2 == 1)
	{
		philo->fork_one = &table->forks[num - 1];
		philo->fork_two = &table->forks[num % table->philo_count];
	}
	else
	{
		philo->fork_one = &table->forks[num % table->philo_count];
		philo->fork_two = &table->forks[num - 1];
	}
}

int	create_start_philo(t_table *table) //TO NORM
{
	int	i;

	i = 0;
	table->philo_list = malloc(sizeof(t_philo) * (table->philo_count + 1));
	if (table->philo_life == 0)
		return (-1);
	while (i < table->philo_count)
	{
		/*table->philo_list[i].fork_one = &table->forks[i];
		table->philo_list[i].fork_two = &table->forks[(i + 1) % table->philo_count];*/
		table->philo_list[i].num = i + 1;
		fork_choice(table, &table->philo_list[i]);
		table->philo_list[i].meal_count = 0;
		table->philo_list[i].start_time = table->start_time;
		table->philo_list[i].philo_count =table->philo_count;
		table->philo_list[i].philo_life = table->philo_life;
		table->philo_list[i].philo_meal = table->philo_meal;
		table->philo_list[i].philo_sleep = table->philo_sleep;
		table->philo_list[i].philo_max_meal = table->philo_max_meal;
		table->philo_list[i].print = &table->print;
		table->philo_list[i].death_auth = &table->death_auth;
		table->philo_list[i].table = table;
		pthread_mutex_init(&table->philo_list[i].pmutex, 0);
		if (pthread_create(&table->philo_list[i].thread_id, NULL, ft_start_thread_philo, &table->philo_list[i]) != 0)
			return (-1);
		printf("philo %d created\n", i + 1);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv) //TO DIVIDE IN FUNCTION(possibly steps for parameter, mutex, thread, join and free & delete)
{
	t_table	table;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	if (parameter_table(argc, argv, &table) == -1)
		return (0);
	while (i < table.philo_count)//!!one more fork for tests with one philo(replace <= with < !!)
	{
		pthread_mutex_init(&table.forks[i], 0);
		i++;
	}
	pthread_mutex_init(&table.death_auth, 0);
	pthread_mutex_init(&table.print, 0);
	printf("gate 5\n");
	//testparam(&table);
	if (create_start_philo(&table) == -1)
		return (0);
	//thread_create monitor thread
	//only create meal_monitor if argc == 6!!
	//pthread_join monitor thread?
	printf("gate 7\n");
	i = 0;
	while (i < table.philo_count)
	{
		pthread_join(table.philo_list[i].thread_id, NULL);
		//printf("gate %d\n", i);
		i++;
	}
	//destroy and free everything mutex !!
	return (0);
}