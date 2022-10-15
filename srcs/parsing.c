/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:33:24 by rokerjea          #+#    #+#             */
/*   Updated: 2022/10/14 14:59:39 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"


/*verifie les arguments pour s'assurer qu'ils sont valides pour ce programme*/
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
	if (j == 0 || j >= 11 || ft_strlen(str) == 0)
		return (-1);
	l = ft_atol(str);
	if (l < 0 || l > 2147483647)
		return (-1);
	return (1);
}

/*assigne les parametres a la structure table et
renvoi -1 ou 1 suivant si ca a echoue ou reussi*/
int	parameter_table(int argc, char **argv, t_table *table)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (checkarg(argv[i]) == -1)
			return (-1);
	}
	if (ft_atol(argv[1]) == 0)
		return (-1);
	table->philo_count = ft_atol(argv[1]);
	table->philo_life = ft_atol(argv[2]);
	table->philo_meal = ft_atol(argv[3]);
	table->philo_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		if (ft_atol(argv[5]) == 0)
			return (-1);
		table->philo_max_meal = ft_atol(argv[5]);
	}
	else
		table->philo_max_meal = -1;
	table->death = 0;
	table->start_time = timestamp_ms();
	return (1);
}
