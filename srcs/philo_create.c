/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:17:02 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/10 14:17:04 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	fork_choice(t_table *table, struct s_philo *philo)
{
	int	num;

	num = philo->num;
	philo->fork_two = &table->forks[num - 1];
	philo->fork_one = &table->forks[num % table->philo_count];
}

void	ft_philo_attributes(t_table *table, int i)
{
	table->philo_list[i].num = i + 1;
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
	table->philo_list[i].last_meal = table->start_time;
}

int	ft_pmutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->philo_list[i].pmutex, 0) != 0)
		{
			while (i-- >= 0)
				pthread_mutex_destroy(&table->philo_list[i].pmutex);
			return (-1);
		}
		i++;
	}
	return (1);
}

//To protect create AND mutex init
int	create_start_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo_list = malloc(sizeof(t_philo) * (table->philo_count + 1));
	if (table->philo_list == 0)
		return (-1);
	if (ft_pmutex(table) == -1)
	{
		free (table->philo_list);
		return (-1);
	}
	while (i < table->philo_count)
	{
		ft_philo_attributes(table, i);
		fork_choice(table, &table->philo_list[i]);
		if (pthread_create(&table->philo_list[i].thread_id, NULL,
				ft_start_thread_philo, &table->philo_list[i]) != 0)
		{
			free (table->philo_list);
			death_cert(table);
			return (-1);
		}
		i++;
	}
	return (1);
}
