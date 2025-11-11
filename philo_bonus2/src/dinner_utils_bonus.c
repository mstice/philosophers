/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:41:40 by mtice             #+#    #+#             */
/*   Updated: 2025/11/10 20:45:19 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//TODO: use a sem
void	death_or_full(t_data *all)
{
	sem_wait(&(all->sem_sim_stop));
	all->stop = true;
	sem_post(&(all->sem_sim_stop));
}

//TODO: incorrect usage of sem
int	no_deaths(t_data *all)
{
	// bool	ret;
	//
	// sem_wait(&(all->sem_sim_stop));
	// if (!all->stop)
	// 	ret = true;
	// else
	// 	ret = false;
	// sem_post(&(all->sem_sim_stop));
	// return (ret);
	// int i;
	//
	// i = -1;
	// while (++i < all->n_philo)
	// {
	// 	if (all->status[i] == DEAD)
	// 		return (0);
	// 	else
	// 		i++;
	// }
	// return (1);
	(void)all;
	return (1);
}

//TODO: use a sem
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
			return (false);
	}
	death_or_full(all);
	return (1);
}

//------------------------------------------------------------------------------
void	print_output(t_data *all, t_philo *philo, t_state action)
{
	if (action != THINK && action != FORK && action != EAT && action != SLEEP
		&& action != DEAD)
		return ;
	if (!no_deaths(all))
		return ;
	sem_wait(&(all->sem_output));
	if (no_deaths(all))
		printf("%-5zu %2d ", time_now(philo->start_time), philo->index);
	if (action == THINK && no_deaths(all))
		printf("is thinking\n");
	else if (action == FORK && no_deaths(all))
		printf("has taken a fork\n");
	else if (action == EAT && no_deaths(all))
		printf("is eating\n");
	else if (action == SLEEP && no_deaths(all))
		printf("is sleeping\n");
	else if (action == DEAD && no_deaths(all))
		printf("died\n");
	sem_post(&(all->sem_output));
}
