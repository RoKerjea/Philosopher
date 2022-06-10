/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:57:53 by rokerjea          #+#    #+#             */
/*   Updated: 2022/06/07 19:57:55 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	ft_mutex_print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo %d is sleeping\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_mutex_print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo %d is thinking\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_mutex_print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo %d has taken a fork\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_mutex_print_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo %d has taken a fork\n", runtime (philo), philo->num);
	printf ("%lld philo %d is eating\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_mutex_print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo %d died\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}
