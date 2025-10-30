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
		printf("died\n");
	pthread_mutex_unlock(&(all->state));
}

//-----------------------------------------------------------------------------
static int	all_eat(t_data *all)
{
	int	i;

	i = 0;
	while (i < all->n_philo)
	{
		if (all->philos[i]->meals == all->must_eat)
			i++;
		else
			return (0);
	}
	return (1);
}

//-----------------------------------------------------------------------------
static void	*philo_routine(void *arg)
{
	t_philo	*which_philo;
	t_data	*all;

	which_philo = (t_philo *)arg;
	all = which_philo->all;
	if (which_philo->index % 2 == 0)
		ft_usleep(1);
	while (42)
	{
		pthread_mutex_lock(which_philo->forks.left_f);
		print_state(all, which_philo, FORK);
		pthread_mutex_lock(which_philo->forks.right_f);
		print_state(all, which_philo, FORK);
		pthread_mutex_lock(&(all->meals));
		print_state(all, which_philo, EAT);
		which_philo->last_meal = time_ms();
		which_philo->meals += 1;
		pthread_mutex_unlock(&(all->meals));
		ft_usleep(all->to_eat);
		pthread_mutex_unlock(which_philo->forks.left_f);
		pthread_mutex_unlock(which_philo->forks.right_f);
		(print_state(all, which_philo, SLEEP), ft_usleep(all->to_sleep));
		print_state(all, which_philo, THINK);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
//TODO: after second while loop, if all philo have eaten, return
static void	*waiter_routine(void *arg)
{
	t_data		*all;
	int			i;

	all = (t_data *)arg;
	while (42)
	{
		i = 0;
		while (i < all->n_philo)
		{
			pthread_mutex_lock(&(all->meals));
			if (time_ms() - all->philos[i]->last_meal >= all->to_die)
			{
				pthread_mutex_unlock(&(all->meals));
				print_state(all, all->philos[i], DEAD);
				pthread_mutex_lock(&(all)->state);
				return (NULL);
			}
			pthread_mutex_unlock(&(all->meals));
			i++;
		}
		if (all_eat(all))
			return (NULL);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
int	start_dinner(t_data *all)
{
	pthread_t	waiter;
	int			i;

	if (pthread_create(&waiter, NULL, &waiter_routine, all))
		return (ft_putstr_fd(ERR_CREATE, 2), 1);
	i = -1;
	while (++i < all->n_philo)
	{
		if (pthread_create(&(all->philos[i]->thread), NULL,
				&philo_routine, all->philos[i]))
			return (ft_putstr_fd(ERR_CREATE, 2), 1);
	}
	i = -1;
	while (++i < all->n_philo)
	{
		if (pthread_detach(all->philos[i]->thread))
			return (ft_putstr_fd(ERR_DETACH, 2), 1);
	}
	if (pthread_join(waiter, NULL))
		return (ft_putstr_fd(ERR_JOIN, 2), 1);
	return (0);
}
