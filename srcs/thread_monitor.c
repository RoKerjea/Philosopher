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
	int x;

	x = 0;
	table = (t_table *) ptr;
	while (1)
	{
		while (x < table->philo_count)//nearly forever or just until end_condition == 1
		{	//!pb, need to mutex lock for access to condition
			pthread_mutex_lock(&table->death_auth);
			if (table->death == 1)//if other monitor find end_condition
			{
				pthread_mutex_unlock(&table->death_auth);
				return ;
			}
			pthread_mutex_unlock(&table->death_auth);
			if (check_last_meal_time(&table->philo_list[x]) == -1)
			{
				pthread_mutex_lock(&table->print);
				printf ("%lld philo %d died\n", runtime (&table->philo_list[x]), x + 1);
				pthread_mutex_unlock(&table->print);
				pthread_mutex_lock(&table->death_auth);
				table->death = 1;
				pthread_mutex_unlock(&table->death_auth);
				return ;//?
			}
			x++;
		}
		//possible need for usleep??
		x = 1;
	}
}

//moniteur de nombre de repas pour tout les philo, meal_monitor TO_TWEAK
void	*ft_meal_monitor_thread(void *ptr)
{
	t_table	*table;
	int x;

	x = 0;
	table = (t_table *) ptr;
	while (x <= table->philo_count)//check end_condition in case the other thread monitor find a death
	{
		pthread_mutex_lock(&table->death_auth);
		if (table->death == 1)//if other monitor find end_condition
		{
			pthread_mutex_unlock(&table->death_auth);
			return ;
		}
		pthread_mutex_unlock(&table->death_auth);
		//need mutex_lock for reading number of meal;
		pthread_mutex_lock(&table->philo_list[x].pmutex);
		if (table->philo_list[x].meal_count >= table->philo_max_meal)
			x++;
		pthread_mutex_unlock(&table->philo_list[x].pmutex);
		/*else
			usleep(100);//to tweak*/
	}
	pthread_mutex_lock(&table->death_auth);
	if (table->death != 1)
		table->death = 1;
	pthread_mutex_unlock(&table->death_auth);
	return ;
}
