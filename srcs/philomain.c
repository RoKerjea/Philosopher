/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philomain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:33:18 by rokerjea          #+#    #+#             */
/*   Updated: 2022/05/13 14:33:20 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d has taken a fork\n", runtime (philo->table), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d has taken a fork\n", runtime (philo->table), philo->philo_number);
	printf ("%lld philo n%d is eating\n", runtime (philo->table), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	philo->last_meal = timestamp_ms();
	usleep(philo->table->philo_meal * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d has released a fork\n", runtime (philo->table), philo->philo_number);
	printf ("%lld philo n%d has released a fork\n", runtime (philo->table), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
}

int	check_sleepdeath(t_philo *philo)
{
	if (philo->table->philo_sleep > philo->last_meal + philo->table->philo_life)
	{
		pthread_mutex_lock(&philo->table->print);
		printf ("%lld philo n%d is sleeping\n", runtime (philo->table), philo->philo_number);
		pthread_mutex_unlock(&philo->table->print);
		usleep(philo->table->philo_life - (timestamp_ms() - philo->last_meal));
		pthread_mutex_lock(&philo->table->print);
		printf ("%lld philo %d died\n", runtime (philo->table), philo->philo_number);
		pthread_mutex_unlock(&philo->table->print);
		if (philo->table->death == 0)
		{
			pthread_mutex_lock(&philo->table->death_auth);
			philo->table->death = 1;
			pthread_mutex_unlock(&philo->table->death_auth);
		}
		return (1);
	}
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (check_sleepdeath(philo) == 1)
		return (0);
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d is sleeping\n", runtime (philo->table), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->table->philo_sleep * 1000);
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d is thinking\n", runtime (philo->table), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

int	check_last_meal_time(t_philo *philo)
{
	long long	now;

	now = timestamp_ms();
	if (now - philo->last_meal >= philo->table->philo_life)
	{
		return (-1);
	}
	return (1);
}

int	stop_condition(t_philo *philo)
{
	if (&philo->table->death == 1)
		return (-1);
	if (check_last_meal_time(philo) == -1)
	{
		pthread_mutex_lock(&philo->table->print);
		printf ("%lld philo %d died\n", runtime (philo->table), philo->philo_number);
		pthread_mutex_unlock(&philo->table->print);
		pthread_mutex_lock(&philo->table->death_auth);
		philo->table->death = 1;
		pthread_mutex_unlock(&philo->table->death_auth);
		return (-1);
	}
	return (1);
}
/*
void	testparam(t_table *table)
{
	printf("number of philo = %d\n", table->philo_count);
	printf("lifetime = %d\n", table->philo_life);
	printf("mealspeed = %d\n", table->philo_meal);
	printf("sleep time = %d\n", table->philo_sleep);
	printf("max meal = %d\n", table->philo_max_meal);

	return ;
}*/

void	*ft_start_thread(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	pthread_mutex_lock(&philo->table->print);
	printf ("this is philo n%d\n", philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	while(stop_condition(philo) == 1)
	{
		if (stop_condition == 1)
			philo_eat(philo);
		if (stop_condition == 1)
			philo_sleep(philo);
	}
	return ;
}

int	create_start_philo(t_table *table)
{
	printf("gate 6\n");
	int	i;

	i = 0;
	table->philo_list = malloc(sizeof(t_philo) * (table->philo_count + 1));
	if (table->philo_life == 0)
		return(-1);
	while (i < table->philo_count)
	{
		table->philo_list[i].left_fork = table->forks[i];
		if (i + 1 > table->philo_count)
			table->philo_list[i].right_fork = table->forks[0];
		else
			table->philo_list[i].right_fork = table->forks[i + 1];
		table->philo_list[i].philo_number = i + 1;
		if (pthread_create(&table->philo_list[i].thread_id, NULL, ft_start_thread, &table->philo_list[i]) != 0)
			return (-1);
		printf("philo %d created\n", i + 1);
		i++;
	}
	printf("gate 7\n");
	return (1);
}

int	main(int argc, char **argv)
{
	int i;

	i = 0;
	t_table table;
	if (argc < 5 || argc > 6)
		return (0);
	if (parameter_table(argc, argv, &table) == -1)
		return (0);
	while (i < table.philo_count)
	{
		pthread_mutex_init(table.forks[i], 0);
		i++;
	}
	printf("gate 5\n");
	//testparam(&table);
	if (create_start_philo(&table) == -1)
		return (0);
	i = 0;
	while (i < table.philo_count)
	{
		pthread_join(table.philo_list[i].thread_id, 0);
		i++;
	}
	return (0);
}
/*TO_DO
elements of routine
death check and write with mutex
*/