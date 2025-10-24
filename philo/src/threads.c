/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:34:55 by mtice             #+#    #+#             */
/*   Updated: 2025/10/23 14:34:20 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static time_t	time_now(time_t start_time)
// {
// 	struct	timeval	tv;
//
// 	if (gettimeofday(&tv, NULL) == -1)
// 		ft_putstr_fd(ERR_TIME, 2);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
// }

static void alone_routine(t_philo *which_philo)
{
	printf("%-5zu %2d has taken a fork\n", time_now(which_philo->start_time), which_philo->index);
	usleep(which_philo->to_die * 1000);
}

//-----------------------------------------------------------------------------
//get time_ms() to be accurate
//TODO: write a function for only one philosopher b4 while loop
static void	*philo_routine(void *arg)
{
	t_philo	*which_philo;

	which_philo = (t_philo *)arg;
	if (which_philo->n_philo == 1)
		return (alone_routine(which_philo), NULL);
	if (which_philo->index % 2 == 0)
		usleep(1);
	while (42 && which_philo->alive == true)
	{
		pthread_mutex_lock(&(which_philo->l_fork));
		printf("%-5zu %2d has taken a fork\n", time_now(which_philo->start_time), which_philo->index);
		pthread_mutex_lock(&(which_philo->r_fork));
		printf("%-5zu %2d has taken a fork\n", time_now(which_philo->start_time), which_philo->index);
		pthread_mutex_lock(&(which_philo->output));
		which_philo->last_meal = time_now(which_philo->start_time);
		which_philo->meals += 1;
		pthread_mutex_unlock(&(which_philo->output));
		usleep(which_philo->to_eat * 1000);
		pthread_mutex_unlock(&(which_philo->l_fork));
		pthread_mutex_unlock(&(which_philo->r_fork));
		printf("%-5zu %2d is sleeping\n", time_now(which_philo->start_time), which_philo->index);
		usleep(which_philo->to_sleep * 1000);
		printf("%-5zu %2d is thinking\n", time_now(which_philo->start_time), which_philo->index);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
//TODO: after second while loop, if all philo have eaten, return
static void	*waiter_routine(void *arg)
{
	t_philo	**all_philos;
	int		i;

	all_philos = (t_philo **)arg;
	while (42)
	{
		i = 0;
		while (i < all_philos[0]->n_philo)
		{
			pthread_mutex_lock(&(all_philos[i]->state));
			if (time_now(all_philos[i]->start_time) - all_philos[i]->last_meal >= all_philos[i]->to_die)
			{
				all_philos[i]->alive = false;
				pthread_mutex_unlock(&(all_philos[i]->state));
				pthread_mutex_lock(&(all_philos[i]->output));
				printf("%-5zu %2d died\n", time_now(all_philos[i]->start_time), all_philos[i]->index); //printing the wrong time
				pthread_mutex_unlock(&(all_philos[i]->output));
				return (NULL);
			}
			pthread_mutex_unlock(&(all_philos[i]->state));
			i++;
		}
		//if all philo ate return (NULL)
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
int	start_dinner(t_data *all)
{
	pthread_t	waiter;
	int			i;

	if (pthread_create(&waiter, NULL, &waiter_routine, all->philos))
		return (printf(ERR_THREAD), 1);
	i = -1;
	while (++i < all->n_philo)
	{
		pthread_mutex_lock(&(all->philos[i]->state));
		all->philos[i]->start_time = start_time();
		all->philos[i]->last_meal = time_now(all->philos[i]->start_time);
		pthread_mutex_unlock(&(all->philos[i]->state));
		if (pthread_create(&(all->philos[i]->thread), NULL, \
		&philo_routine, all->philos[i]))
			return (printf(ERR_THREAD), 1);
	}
	i = -1;
	while (++i < all->n_philo)
	{
		if (pthread_join(all->philos[i]->thread, NULL))
			return (printf(ERR_JOIN), 1);
	}
	if (pthread_join(waiter, NULL))
		return (printf(ERR_JOIN), 1);
	return (0);
}
