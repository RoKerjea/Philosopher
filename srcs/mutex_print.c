/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:57:53 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/14 15:40:12 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*tte les fonctions pour print les messages de changement d'etat
des philosopher, ave mutex lock et unlock immediatement avant et apres*/

void	ft_mutex_print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld %d is sleeping\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_mutex_print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld %d is thinking\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_mutex_print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld %d has taken a fork\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_mutex_print_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld %d has taken a fork\n", runtime (philo), philo->num);
	printf ("%lld %d is eating\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}

void	ft_mutex_print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld %d died\n", runtime (philo), philo->num);
	pthread_mutex_unlock(&philo->table->print);
}
