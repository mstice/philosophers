/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:34:55 by mtice             #+#    #+#             */
/*   Updated: 2025/10/23 14:34:20 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	undead(t_data *all)
// {
// 	int	ret;
//
// 	pthread_mutex_lock(&(all->state));
// 	if (all->stop == true)
// 		ret = 0;
// 	else
// 		ret = 1;
// 	pthread_mutex_unlock(&(all->state));
// 	return (ret);
// }

static void alone_routine(t_philo *which_philo)
{
	printf("%-5zu %2d has taken a fork\n", time_now(which_philo->start_time), which_philo->index);
	usleep(which_philo->all->to_die * 1000);
}

//-----------------------------------------------------------------------------
//get time_ms() to be accurate
//TODO: write a function for only one philosopher b4 while loop
static void	*philo_routine(void *arg)
{
	t_philo	*which_philo;
	t_data	*all;

	which_philo = (t_philo *)arg;
	all = which_philo->all;
	if (all->n_philo == 1)
		return (alone_routine(which_philo), NULL);
	if (which_philo->index % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&(all->meals));
	which_philo->start_time = start_time();
	which_philo->last_meal = start_time();
	pthread_mutex_unlock(&(all->meals));
	while (undead(all))
	{
		printf("%-5zu %2d is thinking\n", time_now(which_philo->start_time), which_philo->index);
		pthread_mutex_lock(&(all->l_fork));
		printf("%-5zu %2d has taken a fork\n", time_now(which_philo->start_time), which_philo->index);
		pthread_mutex_lock(&(all->r_fork));
		printf("%-5zu %2d has taken a fork\n", time_now(which_philo->start_time), which_philo->index);
		pthread_mutex_lock(&(all->meals));
		which_philo->last_meal = time_now(which_philo->start_time);
		which_philo->meals += 1;
		pthread_mutex_unlock(&(all->meals));
		printf("%-5zu %2d is eating\n", time_now(which_philo->start_time), which_philo->index);
		usleep(all->to_eat * 1000);
		pthread_mutex_unlock(&(all->l_fork));
		pthread_mutex_unlock(&(all->r_fork));
		printf("%-5zu %2d is sleeping\n", time_now(which_philo->start_time), which_philo->index);
		usleep(all->to_sleep * 1000);
		// printf("%-5zu %2d is thinking\n", time_now(which_philo->start_time), which_philo->index);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
//TODO: after second while loop, if all philo have eaten, return
static void	*waiter_routine(void *arg)
{
	t_data		*all;
	int		i;

	all = (t_data *)arg;
	while (42)
	{
		i = 0;
		while (i < all->n_philo)
		{
			pthread_mutex_lock(&(all->meals));
			if ((time_now(all->philos[i]->start_time)) - all->philos[i]->last_meal >= all->to_die)
			{
				pthread_mutex_unlock(&(all->meals));
				pthread_mutex_lock(&(all->state));
				all->stop = true;
				pthread_mutex_unlock(&(all->state));
				printf("%-5zu %2d died\n", time_now(all->philos[i]->start_time), all->philos[i]->index); //printing the wrong time
				return (NULL);
			}
			pthread_mutex_unlock(&(all->meals));
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

	if (pthread_create(&waiter, NULL, &waiter_routine, all))
		return (printf(ERR_THREAD), 1);
	i = -1;
	while (++i < all->n_philo)
	{
		if (pthread_create(&(all->philos[i]->thread), NULL, &philo_routine, all->philos[i]))
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
