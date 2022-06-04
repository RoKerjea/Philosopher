/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:33:06 by rokerjea          #+#    #+#             */
/*   Updated: 2022/05/13 14:33:08 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct	s_philo
{
	int	philo_number;
	int	meal_count;
	long long	last_meal;
	pthread_t	thread_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_table	*table;
}				t_philo;

typedef struct	s_table
{
	long long	start_time;
	int philo_count;
	int philo_life;
	int philo_meal;
	int philo_sleep;
	int philo_max_meal;
	int	death;
	pthread_mutex_t	death_auth;
	pthread_mutex_t *forks[300];
	pthread_mutex_t print;
	t_philo *philo_list;
}				t_table;

/*LIB*/

long			ft_atol(const char *str);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *s1);
char			**ft_freetab(char **tab);
unsigned long	ft_strlen(const char *s);

//PARSING.C//

int	parameter_table(int argc, char **argv, t_table *table);
long long	timestamp_ms();
long long	runtime(t_table *table);

/*
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
int pthread_join(pthread_t thread, void **retval);
int pthread_detach(pthread_t thread);

int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *memset(void *s, int c, size_t n);
int gettimeofday(struct timeval *tv, struct timezone *tz);
int usleep(useconds_t usec);
*/

#endif
