/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philomain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:33:18 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/14 14:48:09 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*Toutes les fonctions de setup sont soit appellees soit ecrites ici
et appellees par la fonction main*/

/*destructeur de tout les mutex de tout le projet, soit appellee a la fin 
du programme, soit si il ya un probleme pendant la fonction mutex init
pour s'interrompre de facon "clean"*/
void	ft_mutex_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philo_list[i].pmutex);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->death_auth);
}

/*fonction "d'attente" des thread, une fois que le main a fini sa partie
afin d'attendre que tt les threads aient fini avant de quitter le programme*/
void	ft_thread_join(t_table *table, int argc)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philo_list[i].thread_id, NULL);
		i++;
	}
	pthread_join(table->monitor_id[0], NULL);
	if (argc == 6)
		pthread_join(table->monitor_id[1], NULL);
}

/*fonction pour creer TOUT les threads utilises dans le programme, 
et les envoyer dans leurs fonctions de routine*/
int	ft_thread_create(t_table *table, int argc)
{
	if (create_start_philo(table) == -1)
		return (-1);
	if (pthread_create(&table->monitor_id[0], NULL,
				ft_starve_monitor, table) != 0)
		return (-1);
	if (argc == 6)
		if (pthread_create(&table->monitor_id[1], NULL,
				ft_meal_monitor, table) != 0)
			return (-1);
	return (1);
}

/*initialisation de tout les mutex necessaires pour le projet :
un par fork, 
un par philosopher(pour le time since last meal, et le compte de repas),
un pour print
et un pour signaler une condition d'arret(death)*/
int	ft_mutex_init(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (table->forks == 0)
		return (-1);
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], 0) != 0)
			return (mutex_clean(table, i));
		i++;
	}
	if (pthread_mutex_init(&table->death_auth, 0) != 0)
		return (mutex_clean(table, i));
	if (pthread_mutex_init(&table->print, 0) != 0)
	{
		pthread_mutex_destroy(&table->death_auth);
		return (mutex_clean(table, i));
	}
	return (1);
}

/*fonction main
verifie les arguments et les assignent a la structure principale (table)
initialise les mutex
cree les threads
attends leurs resolution
detruit les mutex
et detruit les donnees sur la heap avant de cloturer le programme*/
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (0);
	if (parameter_table(argc, argv, &table) == -1)
		return (0);
	if (ft_mutex_init(&table) == -1)
		return (0);
	if (ft_thread_create(&table, argc) == -1)
		death_cert(&table);
	ft_thread_join(&table, argc);
	ft_mutex_destroy(&table);
	clean(&table);
	return (0);
}
