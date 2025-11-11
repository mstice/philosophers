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

static void	think_routine(t_data *all, t_philo *philo, bool silent)
{
	time_t	time_to_think;

	if (!no_deaths(all))
		return ;
	pthread_mutex_lock(&(all->meals));
	time_to_think
		= (all->to_die - (time_ms() - philo->last_meal) - all->to_eat)
		/ 2;
	pthread_mutex_unlock (&(all->meals));
	if (time_to_think <= 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!silent)
		print_state(all, philo, THINK);
	ms_sleep(time_to_think);
}

static void	alone_routine(t_data *all, t_philo *philo)
{
	start_delay(all->all_start);
	pthread_mutex_lock(philo->forks.left_f);
	print_state(all, philo, FORK);
	ms_sleep(all->to_die);
	pthread_mutex_unlock(philo->forks.right_f);
}

//-----------------------------------------------------------------------------
static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*all;

	philo = (t_philo *)arg;
	all = philo->all;
	if (all->n_philo == 1)
		return (alone_routine(all, philo), NULL);
	start_delay(all->all_start);
	if (philo->index % 2)
		ms_sleep(all->to_eat);
		//think_routine(all, philo, true);
	while (no_deaths(all))
	{
		pick_up_forks(all, philo);
		pthread_mutex_lock(&(all->meals));
		philo->last_meal = time_ms();
		philo->meals++;
		pthread_mutex_unlock(&(all->meals));
		(print_state(all, philo, EAT), ms_sleep(all->to_eat));
		pthread_mutex_unlock(philo->forks.left_f);
		pthread_mutex_unlock(philo->forks.right_f);
		(print_state(all, philo, SLEEP), ms_sleep(all->to_sleep));
		think_routine(all, philo, false);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
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
				death(all);
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

	assign_start_time(all);
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
	if (pthread_join(waiter, NULL))
		return (ft_putstr_fd(ERR_JOIN, 2), 1);
	while (++i < all->n_philo)
	{
		if (pthread_join(all->philos[i]->thread, NULL))
			return (ft_putstr_fd(ERR_JOIN, 2), 1);
	}
	return (0);
}
