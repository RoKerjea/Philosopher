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

//make a function for philo parameter before phread_create

int	create_start_philo(t_table *table) //TO NORM
{
	int	i;

	i = 0;
	table->philo_list = malloc(sizeof(t_philo) * (table->philo_count + 1));
	if (table->philo_life == 0)
		return (-1);
	while (i < table->philo_count)
	{
		table->philo_list[i].left_fork = &table->forks[i];
		table->philo_list[i].right_fork = &table->forks[(i + 1) % table->philo_count];
		table->philo_list[i].philo_number = i + 1;
		table->philo_list[i].meal_count = 0;
		table->philo_list[i].start_time = table->start_time;
		table->philo_list[i].philo_count =table->philo_count;
		table->philo_list[i].philo_life = table->philo_life;
		table->philo_list[i].philo_meal = table->philo_meal;
		table->philo_list[i].philo_sleep = table->philo_sleep;
		table->philo_list[i].philo_max_meal = table->philo_max_meal;
		table->philo_list[i].print = table->print;
		table->philo_list[i].death_auth = table->death_auth;
		table->philo_list[i].table = table;
		if (pthread_create(&table->philo_list[i].thread_id, NULL, ft_start_thread_philo, &table->philo_list[i]) != 0)
			return (-1);
		printf("philo %d created\n", i + 1);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv) //TO DIVIDE IN FUNCTION(possibly steps for parameter, mutex, thread, join and free & delete)
{
	t_table	table;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	if (parameter_table(argc, argv, &table) == -1)
		return (0);
	while (i <= table.philo_count)//!!one more fork for tests with one philo(replace <= with < !!)
	{
		pthread_mutex_init(&table.forks[i], 0);
		i++;
	}
	pthread_mutex_init(&table.death_auth, 0);
	pthread_mutex_init(&table.print, 0);
	printf("gate 5\n");
	//testparam(&table);
	if (create_start_philo(&table) == -1)
		return (0);
	//thread_create monitor thread
	//only create meal_monitor if argc == 6!!
	//pthread_join monitor thread?
	printf("gate 7\n");
	i = 0;
	while (i < table.philo_count)
	{
		pthread_join(table.philo_list[i].thread_id, NULL);
		//printf("gate %d\n", i);
		i++;
	}
	//destroy every mutex
	return (0);
}
/*TO_DO
elements of routine
death check and write with mutex

thread moniteur de status pour savoir si il ya raison de stop :
un pour verifier philo par philo, si il y a un mort de faim(datarace possible si check and edit of last meal time simultaneous)
et un pour verifier si TOUT les philos ont mange leurs dernier repas et ENSUITE editer stop_condition = 1
Donc
les philos n'ont plus a se preocupper eux meme de savoir si ils ont atteint leurs max de repas
NI
de savoir si ils viennent de mourir
uniquement de verifier si stop_condition == 1 en arreter tout ou continuer normalement
*/