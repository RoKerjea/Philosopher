/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:57:44 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/07 19:57:46 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*ft_starve_monitor(void *ptr)
{
	t_table	*table;
	int		x;

	x = 0;
	table = (t_table *) ptr;
	while (1)
	{
		while (x < table->philo_count && death_check(table) == 1)
		{
			if (death_check(table) == -1)
				return (0);
			if (check_last_meal_time(&table->philo_list[x]) == -1)
			{
				ft_mutex_print_death(&table->philo_list[x]);
				death_cert(table);
				return (0);
			}
			x++;
		}
		if (death_check(table) == -1)
			return (0);
		x = 0;
	}
}

void	*ft_meal_monitor(void *ptr)
{
	t_table	*table;
	int		x;

	x = 0;
	table = (t_table *) ptr;
	while (x <= table->philo_count && death_check(table) == 1)
	{
		if (death_check(table) == -1)
			return (0);
		if (last_meal_check(&table->philo_list[x]) == 1)
			x++;
		else
			usleep(100);
	}
	if (death_check(table) == -1)
		return (0);
	death_cert(table);
	return (0);
}
