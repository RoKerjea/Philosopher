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

#include "./include/philosopher.h"

philo_eat()

philo_sleep()

philo_think()

int	stop_condition()
{
	if (last_meal_time - getttimeofday() <= 0)
	{
		//print "timestamp_in_ms X died";
		table->death = 1;
	}
	if (table->death == 1)
		stop thread;
	return (0)
}

philoroutine()
{
	while(stop_condition == 0)
	{
		if (stop_condition == 0)
			philo_eat();
		if (stop_condition == 0)
			philo_slepp();
		if (stop_condition == 0)
			philo_think();
	}
}

void    main(int argc, char *argv)
{
	int i;

	i = 0;
	t_table table;
	if (argc < 5 || argc > 6)
		return ;
	parameter_table(argc, argv, &table);
	while (i < table.philo_count)
	{
		pthread_mutex_init(table.forks[i], 0);
		i++;
	}
	i = 0;
	table.philo_list = malloc(sizeof(t_philo) * (table.philo_count + 1));
	//protect
	while (i + 1 < table.philo_count)
	{
		pthread_create(table.philo_list[i].thread_id, x, x, x);
		table.philo_list[i].left_fork = table.fork[i];
		table.philo_list[i].right_fork = table.fork[i + 1];
		//start routine?
		i++;
	}
	pthread_create(table.philo_list[i].thread_id, x, x, x);
	table.philo_list[i].left_fork = table.fork[i];
	table.philo_list[i].right_fork = table.fork[0];
	//start routine?
	i = 0;
	while (i < table.philo_count)
	{
		pthread_join(table.philo_list[i].thread_id, 0);
		i++;
	}
	return ;
}
