/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:58:04 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/07 19:58:08 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	philo_update(t_philo *philo)
{
	pthread_mutex_lock(&philo->pmutex);
	philo->meal_count++;
	philo->last_meal = timestamp_ms();
	pthread_mutex_unlock(&philo->pmutex);
}

//make function for lock and print messages
//check end_condition before starting every step
void	philo_eat(t_philo *philo)
{
	if (death_check(philo->table) == -1)
		return ;
	pthread_mutex_lock(philo->fork_one);
	if (death_check(philo->table) == -1)
	{
		pthread_mutex_unlock(philo->fork_one);
		return ;
	}
	ft_mutex_print_fork(philo);
	if (death_check(philo->table) == -1)
	{
		pthread_mutex_unlock(philo->fork_one);
		return ;
	}
	pthread_mutex_lock(philo->fork_two);
	if (death_check(philo->table) == -1)
	{
		pthread_mutex_unlock(philo->fork_one);
		pthread_mutex_unlock(philo->fork_two);
		return ;
	}
	ft_mutex_print_eating(philo);
	philo_update(philo);
	usleep(philo->philo_meal * 1000);
	pthread_mutex_unlock(philo->fork_one);
	pthread_mutex_unlock(philo->fork_two);
}

void	philo_sleep(t_philo *philo)
{
	if (death_check(philo->table) == -1)
		return ;
	ft_mutex_print_sleep(philo);
	usleep(philo->philo_sleep * 1000);
	if (death_check(philo->table) == -1)
		return ;
	ft_mutex_print_think(philo);
	return ;
}

//si philo count even->need delay every second thread
//if philo_count odd->need delay every second of three and every third
//sleep time TO TWEAK !
void	start_delay(t_philo *philo)
{
	if (philo->philo_count % 2 == 0)
	{
		if (philo->num % 2 == 0)
			usleep(1000);
	}
	else
	{
		if (philo->num % 2 == 0)
			usleep(50);
		else if (philo->num % 3 == 0)
		{
			usleep(100);
		}
	}
}

//routine des philo_thread probably DONE TO_CLEAN
void	*ft_start_thread_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	start_delay(philo);
	while (death_check(philo->table) == 1)
	{
		if (death_check(philo->table) == 1)
			philo_eat(philo);
		if (death_check(philo->table) == 1)
			philo_sleep(philo);
	}
	return (NULL);
}
