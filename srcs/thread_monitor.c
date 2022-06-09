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

//moniteur de mort de faim/starve_monitor probablement DONE
void	*ft_starve_monitor_thread(void *ptr)
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
				return ;
			if (check_last_meal_time(&table->philo_list[x]) == -1)
			{
				ft_mutex_print_death(&table->philo_list[x]);
				death_cert(table);
				return ;
			}
			x++;
		}
		if (death_check(table) == -1)
			return ;
		x = 1;
	}
}

//moniteur de nombre de repas pour tout les philo, meal_monitor TO_TWEAK
//sleep time to tweak!!
void	*ft_meal_monitor_thread(void *ptr)
{
	t_table	*table;
	int		x;

	x = 0;
	table = (t_table *) ptr;
	while (x <= table->philo_count && death_check(table) == 1)
	{
		if (death_check(table) == -1)
			return ;
		if (last_meal_check(&table->philo_list[x]) == 1)
			x++;
		else
			usleep(100);
	}
	if (death_check(table) == -1)
		return ;
	death_cert(table);
	return ;
}
