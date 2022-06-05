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



void	testparam(t_table *table)
{
	printf("number of philo = %d\n", table->philo_count);
	printf("lifetime = %d\n", table->philo_life);
	printf("mealspeed = %d\n", table->philo_meal);
	printf("sleep time = %d\n", table->philo_sleep);
	printf("max meal = %d\n", table->philo_max_meal);
	printf("death? = %d\n", table->death);

	return ;
}

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
	philo->meal_count--;
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

int	check_sleepdeath(t_philo *philo)
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
}

int	philo_sleep(t_philo *philo)
{
	if (check_sleepdeath(philo) == 1)
		return (0);
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d is sleeping\n", runtime (philo), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->philo_sleep * 1000);
	pthread_mutex_lock(&philo->table->print);
	printf ("%lld philo n%d is thinking\n", runtime (philo), philo->philo_number);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

int	check_last_meal_time(t_philo *philo)
{
	long long	now;

	now = runtime(philo);
	if (now - philo->last_meal >= philo->philo_life)
	{
		return (-1);
	}
	return (1);
}

int	stop_condition(t_philo *philo)
{
	testparam(philo->table);
	pthread_mutex_lock(&philo->death_auth);
	//printf("gatex0\n");
	if (philo->table->death == 1)
		return (-1);
	//printf("gatex00\n");
	pthread_mutex_unlock(&philo->death_auth);
	//printf("gatex1\n");
	if (philo->meal_count == philo->philo_max_meal)
		return (-1);
	//printf("gatex2\n");
	if (check_last_meal_time(philo) == -1)
	{
		pthread_mutex_lock(&philo->table->print);
		printf ("%lld philo %d died\n", runtime (philo), philo->philo_number);
		pthread_mutex_unlock(&philo->table->print);
		pthread_mutex_lock(&philo->table->death_auth);
		philo->table->death = 1;
		pthread_mutex_unlock(&philo->table->death_auth);
		return (-1);
	}
	return (1);
}
void	ft_test_philo_data(t_philo *philo)
{
	printf("number of philo actual = %d\n", philo->philo_number);
	printf("lifetime = %d\n", philo->philo_life);
	printf("mealspeed = %d\n", philo->philo_meal);
	printf("sleep time = %d\n", philo->philo_sleep);
	printf("max meal = %d\n", philo->philo_max_meal);
	return ;
}
void	*ft_start_thread(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	ft_test_philo_data(philo);
	/*if (philo->philo_number % 2 == 1)
		usleep(philo->philo_meal / 10);*/
	printf("gatex\n");
	pthread_mutex_lock(&philo->print);
	printf ("this is philo n%d\n", philo->philo_number);
	pthread_mutex_unlock(&philo->print);
	printf("gatexy\n");
	while (stop_condition(philo) == 1)
	{
		if (stop_condition(philo) == 1)
			philo_eat(philo);
		if (stop_condition(philo) == 1)
			philo_sleep(philo);
	}
	return (NULL);
}

int	create_start_philo(t_table *table)
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
		//assign param from table to philo
		if (pthread_create(&table->philo_list[i].thread_id, NULL, ft_start_thread, &table->philo_list[i]) != 0)
			return (-1);
		printf("philo %d created\n", i + 1);
		i++;
	}
	//printf("gate 7\n");
	return (1);
}

int	main(int argc, char **argv)
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
	pthread_mutex_lock(&table.print);
	printf("gate 6\n");
	pthread_mutex_unlock(&table.print);
	if (create_start_philo(&table) == -1)
		return (0);
	printf("gate 7\n");
	i = 0;
	while (i < table.philo_count)
	{
		pthread_join(table.philo_list[i].thread_id, NULL);
		printf("gate %d\n", i);
		i++;
	}
	return (0);
}
/*TO_DO
elements of routine
death check and write with mutex
thread moniteur de status pour savoir si il ya raison de stop
un pour verifier philo par philo, si il y a un mort de faim(datarace possible si check and edit of last meal time simultaneous)
et un pour verifier si TOUT les philos ont mange leurs dernier repas et ENSUITE editer stop_condition = 1
Donc
les philos n'ont plus a se preocupper eux meme de savoir si ils ont atteint leurs max de repas
NI
de savoir si ils viennent de mourir
uniquement de verifier si stop_condition == 1 en arreter tout ou continuer normalement
*/