/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:35:57 by mtice             #+#    #+#             */
/*   Updated: 2025/11/13 18:29:36 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//------------------------------------------------------------------------------
//sets the stop flag to stop the routines
void	stop(t_data *all)
{
	pthread_mutex_lock(&(all->m_stop));
	all->stop = true;
	pthread_mutex_unlock(&(all->m_stop));
}

//-----------------------------------------------------------------------------
//checks if all philos are alive
bool	alive(t_data *all)
{
	int	ret;

	pthread_mutex_lock(&(all->m_stop));
	if (!all->stop)
		ret = true;
	else
		ret = false;
	pthread_mutex_unlock(&(all->m_stop));
	return (ret);
}

//-----------------------------------------------------------------------------
//checks if all philos have had enough to eat
bool	enough(t_data *all)
{
	int	i;

	if (all->must_eat == 0)
		return (false);
	i = 0;
	while (i < all->n_philo)
	{
		if (all->philos[i]->meals >= all->must_eat)
			i++;
		else
			return (false);
	}
	return (true);
}

//-----------------------------------------------------------------------------
void	print_output(t_data *all, t_philo *philo, t_state action)
{
	if (action != THINK && action != FORK && action != EAT && action != SLEEP
		&& action != DEAD)
		return ;
	if (!alive(all))
		return ;
	pthread_mutex_lock(&(all->m_output));
	if (action != DEAD)
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
		printf("%-5zu %2d died\n", time_now(philo->start_time), philo->index);
	pthread_mutex_unlock(&(all->m_output));
}

//-----------------------------------------------------------------------------
//all philos are left handed, except for the last philo
void	pick_up_forks(t_data *all, t_philo *philo)
{
	if (philo->index != all->n_philo)
	{
		pthread_mutex_lock(philo->forks.left_f);
		print_output(all, philo, FORK);
		pthread_mutex_lock(philo->forks.right_f);
		print_output(all, philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->forks.right_f);
		print_output(all, philo, FORK);
		pthread_mutex_lock(philo->forks.left_f);
		print_output(all, philo, FORK);
	}
}
