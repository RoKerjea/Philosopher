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

//copy data from table to philo
void	ft_philo_attributes(t_table *table)
{

}

//TO NORM
int	create_start_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo_list = malloc(sizeof(t_philo) * (table->philo_count + 1));
	if (table->philo_list == 0)
		return (-1);
	while (i < table->philo_count)
	{
		table->philo_list[i].num = i + 1;
		fork_choice(table, &table->philo_list[i]);
		table->philo_list[i].meal_count = 0;
		table->philo_list[i].start_time = table->start_time;
		table->philo_list[i].philo_count = table->philo_count;
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
		i++;
	}
	return (1);
}

void	ft_mutex_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philo_list[i].pmutex);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->death_auth);
}

void	ft_thread_join(t_table *table, int argc)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philo_list[i].thread_id, NULL);
		i++;
	}
	pthread_join(table->monitor_id[0], NULL);
	if (argc == 6)
	{
		pthread_join(table->monitor_id[1], NULL);
	}	
}

//need to protect pthread_create!!
int	ft_thread_create(t_table *table, int argc)
{
	if (create_start_philo(&table) == -1)
		return (0);
	pthread_create(&table->monitor_id[0], NULL, ft_starve_monitor_thread, table);
	if (argc == 6)
	{
		pthread_create(&table->monitor_id[1], NULL, ft_meal_monitor_thread, table);
	}
	return (1);
}

void	ft_mutex_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_init(&table->forks[i], 0);
		i++;
	}
	pthread_mutex_init(&table->death_auth, 0);
	pthread_mutex_init(&table->print, 0);
}

//TO DIVIDE IN FUNCTION
//(possibly steps for parameter, mutex, thread, join and free & delete)
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (0);
	if (parameter_table(argc, argv, &table) == -1)
		return (0);
	ft_mutex_init(&table);
	ft_thread_create(&table, argc);
	ft_thread_join(&table, argc);
	ft_mutex_destroy(&table);
	free (table.philo_list);
	return (0);
}
//free everything !!
