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

int	brainstorm(struct s_philo *philo, int forks)
{
	int	res;

	res = 1;
	if (death_check(philo->table) == -1)
	{
		res = -1;
		pthread_mutex_unlock(philo->fork_one);
		if (forks == 2)
			pthread_mutex_unlock(philo->fork_two);
	}
	return (res);
}

void	philo_eat(t_philo *philo)
{
	if (death_check(philo->table) == -1)
		return ;
	pthread_mutex_lock(philo->fork_one);
	if (brainstorm(philo, 1) == -1)
		return ;
	ft_mutex_print_fork(philo);
	if (philo->philo_count == 1)
		usleep((philo->philo_life + 100) * 1000);
	if (brainstorm(philo, 1) == -1)
		return ;
	pthread_mutex_lock(philo->fork_two);
	if (brainstorm(philo, 2) == -1)
		return ;
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

void	start_delay(t_philo *philo)
{
	if (philo->philo_count % 2 == 0)
	{
		if (philo->num % 2 == 0)
			usleep(philo->philo_meal * 100);
	}
	else if (philo->philo_count > 2)
	{
		if (philo->num % 2 == 0)
			usleep(philo->philo_meal * 100);
		else if (philo->num % 3 == 0)
		{
			usleep(philo->philo_meal * 1000);
		}
	}
}

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
