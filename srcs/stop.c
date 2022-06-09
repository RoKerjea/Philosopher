/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:05:00 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/09 16:05:04 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	death_cert(t_table *table)
{
	pthread_mutex_lock(&table->death_auth);
	if (table->death != 1)
		table->death = 1;
	pthread_mutex_unlock(&table->death_auth);
}

int	death_check(t_table *table)
{
	int	res;

	res = 1;
	pthread_mutex_lock(&table->death_auth);
	if (table->death == 1)
		res = -1;
	pthread_mutex_unlock(&table->death_auth);
	return (res);
}

int	last_meal_check(t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->pmutex);
	if (philo->meal_count >= philo->philo_max_meal)
		res = 1;
	pthread_mutex_unlock(&philo->pmutex);
	return (res);
}
