/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:57:35 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/07 19:57:37 by rokerjea         ###   ########.fr       */
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

int	check_last_meal_time(t_philo *philo)
{
	long long	now;
	int			res;

	res = 1;
	now = timestamp_ms();
	pthread_mutex_lock(&philo->pmutex);
	if (now - philo->last_meal >= philo->philo_life)
		res = -1;
	pthread_mutex_unlock(&philo->pmutex);
	return (res);
}

long long	timestamp_ms(void)
{
	struct timeval	time_now;
	long long		res;

	gettimeofday(&time_now, 0);
	res = time_now.tv_sec * 1000 + time_now.tv_usec / 1000;
	return (res);
}

long long	runtime(struct s_philo *philo)
{
	long long	res;

	res = timestamp_ms() - philo->start_time;
	return (res);
}

void	ft_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_auth);
	pthread_mutex_unlock(&philo->table->death_auth);
	pthread_mutex_lock(&philo->pmutex);
	philo->start_time = philo->table->start_time;
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->pmutex);
}