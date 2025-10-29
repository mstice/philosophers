/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:34:55 by mtice             #+#    #+#             */
/*   Updated: 2025/10/28 12:08:48 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_time_ms();
	while (get_time_ms() - start < mls)
		usleep (500);
}

static time_t	time_now(time_t start_time)
{
	return (get_time_ms() - start_time);
}
//-----------------------------------------------------------------------------
static void	print_state(t_data *all, t_philo *philo, char action)
{
	if (action != THINK && action != FORK && action != EAT && action != SLEEP
		&& action != DEAD)
		return ;
	pthread_mutex_lock(&(all->state));
	printf("%-5zu %2d ", time_now(philo->start_time), philo->index);
	if (action == THINK)
		printf("is thinking\n");
	else if (action == FORK)
		printf("has taken a fork\n");
	else if (action == EAT)
		printf("is eating\n");
	else if (action == SLEEP)
		printf("is sleeping\n");
	else if (action == DEAD)
	{
		printf("died\n");
		pthread_join(philo->thread, NULL);
	}
	pthread_mutex_unlock(&(all->state));
}

static int	undead(t_data *all)
{
	int	ret;

	pthread_mutex_lock(&(all->over));
	if (all->stop == true)
		ret = 0;
	else
		ret = 1;
	pthread_mutex_unlock(&(all->over));
	return (ret);
}

// static void alone_routine(t_philo *which_philo)
// {
// 	print_state(which_philo->all, which_philo, FORK);
// 	ft_usleep(which_philo->all->to_die);
// }

//-----------------------------------------------------------------------------
//get time_ms() to be accurate
static void	*philo_routine(void *arg)
{
	t_philo	*which_philo;
	t_data	*all;

	which_philo = (t_philo *)arg;
	all = which_philo->all;
	// if (all->n_philo == 1)
	// 	return (alone_routine(which_philo), NULL);
	if (which_philo->index % 2 == 0)
		ft_usleep(1);
	while (undead(all))
	{
		//printf("%-5zu %2d is thinking\n", time_now(which_philo->start_time), which_philo->index);
		pthread_mutex_lock(which_philo->forks.left_f);
		print_state(all, which_philo, FORK);
		pthread_mutex_lock(which_philo->forks.right_f);
		print_state(all, which_philo, FORK);
		pthread_mutex_lock(&(all->meals));
		print_state(all, which_philo, EAT);
		which_philo->last_meal = get_time_ms();
		which_philo->meals += 1;
		pthread_mutex_unlock(&(all->meals));
		ft_usleep(all->to_eat);
		pthread_mutex_unlock(which_philo->forks.left_f);
		pthread_mutex_unlock(which_philo->forks.right_f);
		print_state(all, which_philo, SLEEP);
		ft_usleep(all->to_sleep);
		print_state(all, which_philo, THINK);
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
			if (get_time_ms() - all->philos[i]->last_meal >= all->to_die)
			{
				pthread_mutex_unlock(&(all->meals));
				print_state(all, all->philos[i], DEAD);
				pthread_mutex_lock(&(all->over));
				all->stop = true;
				pthread_mutex_unlock(&(all->over));
				pthread_mutex_lock(&(all)->state);
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
