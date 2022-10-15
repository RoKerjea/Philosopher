/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   problem_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:58:22 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/14 15:07:40 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*fonctions de nettoyage pour cloturer le programme proprement*/

int	mutex_clean(t_table *table, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i--;
	}
	if (table->forks != 0)
		free (table->forks);
	return (-1);
}

void	clean(t_table *table)
{
	if (table->philo_list != 0)
		free (table->philo_list);
	if (table->forks != 0)
		free (table->forks);
}
