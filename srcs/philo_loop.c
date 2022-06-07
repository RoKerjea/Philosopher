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

//make function for lock and print messages
//check end_condition before starting every step
void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d has taken a fork\n", runtime (philo), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d has taken a fork\n", runtime (philo), philo->philo_number);
	printf ("%lld philo n%d is eating\n", runtime (philo), philo->philo_number);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->table->print);
	philo->last_meal = timestamp_ms();
	usleep(philo->philo_meal * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	/*pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d has released a fork\n", runtime (philo), philo->philo_number);
	printf ("%lld philo n%d has released a fork\n", runtime (philo), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);*/
}

/*????
int	check_sleepdeath(t_philo *philo)//can it be completly replaced by thread monitor?
{
	if (philo->philo_sleep > philo->last_meal + philo->philo_life)
	{
		pthread_mutex_lock(&philo->table->print);
		printf ("%lld philo n%d is sleeping\n", runtime (philo), philo->philo_number);
		pthread_mutex_unlock(&philo->table->print);
		usleep(philo->philo_life - (timestamp_ms() - philo->last_meal));
		pthread_mutex_lock(&philo->table->print);
		printf ("%lld philo %d died\n", runtime (philo), philo->philo_number);
		pthread_mutex_unlock(&philo->table->print);
		pthread_mutex_lock(&philo->table->death_auth);
		if (philo->table->death == 0)
		{
			philo->table->death = 1;
		}
		pthread_mutex_unlock(&philo->table->death_auth);
		return (1);
	}
	return (0);
}*/

//make function for lock and print messages
//check end_condition before starting every step
int	philo_sleep(t_philo *philo)
{
	/*if (check_sleepdeath(philo) == 1)
		return (0);*/
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d is sleeping\n", runtime (philo), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->philo_sleep * 1000);
	//check endcondition before next task, if death_monitor did his job,
	//no need for philo_thread to check himself if death during sleep
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d is thinking\n", runtime (philo), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

//probably DONE
int	stop_condition(t_philo *philo)
{
	int	res;

	res = 1;
	pthread_mutex_lock(&philo->death_auth);
	if (philo->table->death == 1)
		res = -1;
	pthread_mutex_unlock(&philo->death_auth);
	return (res);
}

//routine des philo_thread probably DONE TO_CLEAN
void	*ft_start_thread_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	//ft_test_philo_data(philo);
	/*if (philo->philo_number % 2 == 1)
		usleep(philo->philo_meal / 10);*/
	//printf("gatex\n");
	pthread_mutex_lock(&philo->print);
	//printf ("this is philo n%d\n", philo->philo_number);
	pthread_mutex_unlock(&philo->print);
	//printf("gatexy\n");
	while (stop_condition(philo) == 1)
	{
		if (stop_condition(philo) == 1)
			philo_eat(philo);
		if (stop_condition(philo) == 1)
			philo_sleep(philo);
	}
	return (NULL);
}
