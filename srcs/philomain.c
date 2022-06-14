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
		pthread_join(table->monitor_id[1], NULL);
}

int	ft_thread_create(t_table *table, int argc)
{
	pthread_mutex_lock(&table->death_auth);
	if (create_start_philo(table) == -1)
		return (-1);
	if (pthread_create(&table->monitor_id[0], NULL,
			ft_starve_monitor, table) != 0)
		return (-1);
	if (argc == 6)
		if (pthread_create(&table->monitor_id[1], NULL,
				ft_meal_monitor, table) != 0)
			return (-1);	
	table->start_time = timestamp_ms();
	pthread_mutex_unlock(&table->death_auth);
	return (1);
}

int	ft_mutex_init(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (table->forks == 0)
		return (-1);
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], 0) != 0)
			return (mutex_clean(table, i));
		i++;
	}
	if (pthread_mutex_init(&table->death_auth, 0) != 0)
		return (mutex_clean(table, i));
	if (pthread_mutex_init(&table->print, 0) != 0)
	{
		pthread_mutex_destroy(&table->death_auth);
		return (mutex_clean(table, i));
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (0);
	if (parameter_table(argc, argv, &table) == -1)
		return (0);
	if (ft_mutex_init(&table) == -1)
		return (0);
	if (ft_thread_create(&table, argc) == -1)
		death_cert(&table);
	ft_thread_join(&table, argc);
	ft_mutex_destroy(&table);
	clean(&table);
	return (0);
}
