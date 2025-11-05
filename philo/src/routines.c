/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:34:55 by mtice             #+#    #+#             */
/*   Updated: 2025/11/04 14:59:15 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void think_routine(t_data *all, t_philo *which_philo, bool silent)
{
	time_t time_to_think;

	if (!no_deaths(all))
		return ;
	pthread_mutex_lock(&(all->meals));
	time_to_think = (all->to_die - (time_ms() - which_philo->last_meal) - all->to_eat) / 2;
	pthread_mutex_unlock (&(all->meals));
	if (time_to_think <= 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	else if (time_to_think > 600)
		time_to_think = 200;
	if (!silent)
		print_state(all, which_philo, THINK);
	ft_usleep(time_to_think);
}

static void	alone(t_philo *which_philo)
{
	print_state(which_philo->all, which_philo, FORK);
	ft_usleep(which_philo->all->to_die);
}

//-----------------------------------------------------------------------------
static void	*philo_routine(void *arg)
{
	t_philo	*which_philo;
	t_data	*all;

	which_philo = (t_philo *)arg;
	all = which_philo->all;
	// sim_start_delay(all->all_start);
	if (all->n_philo == 1) //maybe there is a way to avoid this;
		return (alone(which_philo), NULL);
	pthread_mutex_lock(&(all->meals));
	which_philo->last_meal = all->all_start;
	which_philo->start_time = all->all_start;
	pthread_mutex_unlock(&(all->meals));
	sim_start_delay(all->all_start);
	//which_philo->start_time = all->all_start;
	if (which_philo->index % 2)
		think_routine(all, which_philo, true);
	while (no_deaths(all))
	{
		if (which_philo->index != all->n_philo)
		{
			pthread_mutex_lock(which_philo->forks.left_f);
			print_state(all, which_philo, FORK);
			pthread_mutex_lock(which_philo->forks.right_f);
			print_state(all, which_philo, FORK);
		}
		else
		{
			pthread_mutex_lock(which_philo->forks.right_f);
			print_state(all, which_philo, FORK);
			pthread_mutex_lock(which_philo->forks.left_f);
			print_state(all, which_philo, FORK);
		}
		pthread_mutex_lock(&(all->meals));
		print_state(all, which_philo, EAT);
		which_philo->last_meal = time_ms();
		which_philo->meals += 1;
		pthread_mutex_unlock(&(all->meals));
		ft_usleep(all->to_eat);
		pthread_mutex_unlock(which_philo->forks.left_f);
		pthread_mutex_unlock(which_philo->forks.right_f);
		(print_state(all, which_philo, SLEEP), ft_usleep(all->to_sleep));
		think_routine(all, which_philo, false);
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
		while (i < all->n_philo) // && no_deaths(all)
		{
			pthread_mutex_lock(&(all->meals));
			if (time_ms() - all->philos[i]->last_meal >= all->to_die)
			{
				pthread_mutex_unlock(&(all->meals));
				print_state(all, all->philos[i], DEAD);
				death(all);
				return (NULL);
			}
			pthread_mutex_unlock(&(all->meals));
			i++;
		}
		if (all->must_eat > 0 && all_eat(all))
			return (NULL);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
int	start_dinner(t_data *all)
{
	pthread_t	waiter;
	int			i;

	all->all_start = time_ms() + (all->n_philo * 2 * 10); //magic numbers
	if (pthread_create(&waiter, NULL, &waiter_routine, all))
		return (ft_putstr_fd(ERR_CREATE, 2), 1);
	i = -1;
	while (++i < all->n_philo)
	{
		all->philos[i]->start_time = all->all_start;
		all->philos[i]->last_meal = all->all_start;
		if (pthread_create(&(all->philos[i]->thread), NULL,
				&philo_routine, all->philos[i]))
			return (ft_putstr_fd(ERR_CREATE, 2), 1);
	}
	i = -1;
	if (pthread_join(waiter, NULL))
		return (ft_putstr_fd(ERR_JOIN, 2), 1);
	while (++i < all->n_philo)
	{
		if (pthread_join(all->philos[i]->thread, NULL))
			return (ft_putstr_fd(ERR_JOIN, 2), 1);
	}
	return (0);
}
