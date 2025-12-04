/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:34:55 by mtice             #+#    #+#             */
/*   Updated: 2025/11/13 18:27:57 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//-----------------------------------------------------------------------------
//how long a philo should think for after sleeping before grabbing a fork
static void	think_routine(t_data *all, t_philo *philo)
{
	time_t	time_to_think;

	if (!alive(all))
		return ;
	pthread_mutex_lock(&(all->m_meals));
	time_to_think
		= (all->to_die - (time_ms() - philo->last_meal) - all->to_eat)
		/ 2;
	pthread_mutex_unlock (&(all->m_meals));
	if (time_to_think <= 0)
		return ;
	if (time_to_think > 600)
		time_to_think = 200;
	print_output(all, philo, THINK);
	ms_sleep(time_to_think);
}

//-----------------------------------------------------------------------------
//routine for the case where there is only one philo and one fork
static void	alone_routine(t_data *all, t_philo *philo)
{
	start_delay(all->all_start);
	pthread_mutex_lock(philo->forks.left_f);
	print_output(all, philo, FORK);
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
		(print_output(all, philo, THINK), usleep(all->to_eat * 1000));
	while (alive(all))
	{
		pick_up_forks(all, philo);
		pthread_mutex_lock(&(all->m_meals));
		philo->last_meal = time_ms();
		philo->meals++;
		pthread_mutex_unlock(&(all->m_meals));
		(print_output(all, philo, EAT), ms_sleep(all->to_eat));
		pthread_mutex_unlock(philo->forks.left_f);
		pthread_mutex_unlock(philo->forks.right_f);
		(print_output(all, philo, SLEEP), ms_sleep(all->to_sleep));
		think_routine(all, philo);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
//separate thread acts as a "waiter" checks if anyone died or finished eating
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
			pthread_mutex_lock(&(all->m_meals));
			if (time_ms() - all->philos[i]->last_meal >= all->to_die)
			{
				pthread_mutex_unlock(&(all->m_meals));
				print_output(all, all->philos[i], DEAD);
				stop(all);
				return (NULL);
			}
			pthread_mutex_unlock(&(all->m_meals));
			i++;
		}
		if (enough(all) || !alive(all))
			return (stop(all), NULL);
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
	if (pthread_join(waiter, NULL))
		return (ft_putstr_fd(ERR_JOIN, 2), 1);
	i = -1;
	while (++i < all->n_philo)
	{
		if (pthread_join(all->philos[i]->thread, NULL))
			return (ft_putstr_fd(ERR_JOIN, 2), 1);
	}
	return (0);
}
