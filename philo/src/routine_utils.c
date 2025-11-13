/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:35:57 by mtice             #+#    #+#             */
/*   Updated: 2025/11/04 14:59:14 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death(t_data *all)
{
	pthread_mutex_lock(&(all->sim_stop));
	all->stop = true;
	pthread_mutex_unlock(&(all->sim_stop));
}

int	no_deaths(t_data *all)
{
	int	ret;

	pthread_mutex_lock(&(all->sim_stop));
	if (!all->stop)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&(all->sim_stop));
	return (ret);
}

//-----------------------------------------------------------------------------
int	all_eat(t_data *all)
{
	int	i;

	if (all->must_eat == 0)
		return (0);
	i = 0;
	while (i < all->n_philo)
	{
		if (all->philos[i]->meals >= all->must_eat)
			i++;
		else
			return (0);
	}
	death(all);
	return (1);
}

//-----------------------------------------------------------------------------
void	print_state(t_data *all, t_philo *philo, t_state action)
{
	if (action != THINK && action != FORK && action != EAT && action != SLEEP
		&& action != DEAD)
		return ;
	if (!no_deaths(all))
		return ;
	pthread_mutex_lock(&(all->state));
	// if (no_deaths(all))
	// {
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
	// }
	else if (action == DEAD)
		printf("%-5zu %2d died\n", time_now(philo->start_time), philo->index);
	pthread_mutex_unlock(&(all->state));
}

//-----------------------------------------------------------------------------
void	pick_up_forks(t_data *all, t_philo *philo)
{
	if (philo->index != all->n_philo)
	{
		pthread_mutex_lock(philo->forks.left_f);
		print_state(all, philo, FORK);
		pthread_mutex_lock(philo->forks.right_f);
		print_state(all, philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->forks.right_f);
		print_state(all, philo, FORK);
		pthread_mutex_lock(philo->forks.left_f);
		print_state(all, philo, FORK);
	}
}
