/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:57:33 by mtice             #+#    #+#             */
/*   Updated: 2025/11/10 20:48:02 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

#define N 5
#define DIE 310
#define EAT 100
#define SLEEP 200
#define MEALS 10

typedef enum e_status
{
	THINKING,
	HUNGRY,
	EATING
}			t_status;

t_status state[N];
pthread_mutex_t critical_region_mtx;
pthread_mutex_t output_mtx;
sem_t both_forks_available[N];

size_t left(size_t i)
{
	return ((i - 1 + N) % N);
}

size_t right(size_t i)
{
	return ((i + 1) % N);
}

void test(size_t i)
{
	if (state[i] == HUNGRY && state[left(i)] != EATING && state[right(i)] != EATING)
	{
		state[i] = EATING;
		sem_post(&both_forks_available[i]);
	}
}

void think(size_t i)
{
	//TODO:
	size_t duration;
	if (i % 2)
		duration = 1;
	else {
		duration = 0;
	}
	pthread_mutex_lock(&output_mtx);
	printf("%zu is thinking for %zu ms\n", i, duration);
	pthread_mutex_unlock(&output_mtx);
	usleep(duration * 1000);
}

void take_forks(size_t i)
{
	pthread_mutex_lock(&critical_region_mtx);
	state[i] = HUNGRY;
	pthread_mutex_lock(&output_mtx);
	printf("%zu is HUNGRY\n", i);
	pthread_mutex_unlock(&output_mtx);
	test(i);
	pthread_mutex_unlock(&critical_region_mtx);
	sem_wait(&both_forks_available[i]);
}

void eat(size_t i)
{
	size_t duration = EAT;
	pthread_mutex_lock(&output_mtx);
	printf("%zu is eating for %zu ms\n", i, duration);
	pthread_mutex_unlock(&output_mtx);
	usleep(duration * 1000);
}

void put_forks(size_t i)
{
	pthread_mutex_lock(&critical_region_mtx);
	state[i] = THINKING;
	test(left(i));
	test(right(i));
	pthread_mutex_unlock(&critical_region_mtx);
}

void	*philosopher(void *arg)
{
	size_t i = (size_t)arg;
	while (42)
	{
		think(i);
		take_forks(i);
		eat(i);
		put_forks(i);
	}
	return (NULL);
}

int	main(void)
{
	size_t i;
	pthread_t	threads[N];

	pthread_mutex_init(&critical_region_mtx, NULL);
	pthread_mutex_init(&output_mtx, NULL);
	i = 0;
	while (i < N)
		sem_init(&both_forks_available[i], 0, 0), i++;
	i = 0;
	while (i < N)
		pthread_create(&threads[i], NULL, philosopher, (void *)i), i++;
	i = 0;
	while (i < N)
		pthread_join(threads[i], NULL), i++;
	pthread_mutex_destroy(&critical_region_mtx);
	pthread_mutex_destroy(&output_mtx);
	i = 0;
	while (i < N)
		sem_destroy(&both_forks_available[i]), i++;
	return (0);
}
