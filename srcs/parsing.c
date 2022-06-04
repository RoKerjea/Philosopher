/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:33:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/05/13 14:33:25 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	checkarg(char *str)
{
	int		i;
	int		j;
	long	l;

	i = 0;
	j = 0;
	if (str[i] == '-')
		i++;
	while (str[i] == 0)
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if (str[i] >= '0' && str[i] <= '9')
			j++;
		i++;
	}
	if (j == 0 || j >= 11)
		return (-1);
	l = ft_atol(str);
	if (l < -2147483648 || l > 2147483647)
		return (-1);
	return (1);
}

long long timestamp_ms()
{
	struct	timeval time_now;
	long long	res;

	gettimeofday(&time_now, 0);
	res = time_now.tv_sec * 1000 + time_now.tv_usec / 1000;
	return (res);
}

long long	runtime(t_table *table)
{
	long long	res;

	res = timestamp_ms() - table->start_time;
	return (res);
}

int	parameter_table(int argc, char **argv, t_table *table)
{
	printf("gate 2\n");
	int	i;

	i = 1;
	while (i < argc)
	{
		if (checkarg(argv[i]) == -1)
		{
			return (-1);
		}
		printf("arg %i checked\n", i);
		i++;
	}
	printf("gate 1\n");
	table->philo_count = ft_atol(argv[1]);
	table->philo_life = ft_atol(argv[2]);
	table->philo_meal = ft_atol(argv[3]);
	table->philo_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->philo_max_meal = ft_atol(argv[5]);
	else
		table->philo_max_meal = -1;

	pthread_mutex_lock(&table->death_auth);
	table->death = 0;
	pthread_mutex_unlock(&table->death_auth);
	table->start_time = timestamp_ms();
	return (1);
}
