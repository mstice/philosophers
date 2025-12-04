/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:41:40 by mtice             #+#    #+#             */
/*   Updated: 2025/11/18 20:06:36 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//-----------------------------------------------------------------------------
//special routine for 1 philosopher 1 fork case
void	alone_routine(t_data *all, t_philo *philo)
{
	start_delay(all->all_start);
	sem_wait(all->sem_cutlery);
	print_output(all, philo, FORK);
	ms_sleep(all->to_die);
	sem_post(all->sem_cutlery);
	ft_exit(all, &(philo->pwaiter), DEAD);
}

//-----------------------------------------------------------------------------
//checks whether a philo is alive
//bool philo_routine: true if the check comes from the philo_routine
bool	alive(t_data *all, t_philo *philo, bool philo_routine)
{
	bool	ret;

	sem_wait(all->sem_meals);
	if (time_ms() - philo->last_meal >= all->to_die)
		ret = false;
	else
		ret = true;
	sem_post(all->sem_meals);
	if (ret == false && philo_routine == true)
	{
		sem_post(all->sem_cutlery);
		sem_post(all->sem_cutlery);
	}
	return (ret);
}

//-----------------------------------------------------------------------------
//returns true if philo has consumed enough meals
bool	enough_meals(t_data *all, t_philo *philo)
{
	bool	ret;

	if (all->must_eat == 0)
		return (false);
	sem_wait(all->sem_meals);
	if (philo->meals >= all->must_eat)
		ret = true;
	else
		ret = false;
	sem_post(all->sem_meals);
	return (ret);
}

//-----------------------------------------------------------------------------
//sends a signal to all kill philosophers
//if a philo has terminated, skips sending the signal to that philo
void	kill_all(t_data *all)
{
	int	i;

	i = -1;
	while (++i < all->n_philo)
	{
		if (kill(all->pids[i], SIGKILL) == -1)
		{
			if (errno == ESRCH)
				continue ;
			ft_putstr_fd(ERR_KILL, 2);
			free_all(all);
			exit(EXIT_FAILURE);
		}
	}
}

//------------------------------------------------------------------------------
void	print_output(t_data *all, t_philo *philo, t_state action)
{
	if (action != THINK && action != FORK && action != EAT && action != SLEEP
		&& action != DEAD)
		return ;
	sem_wait(all->sem_stop);
	if (all->stop == true)
	{
		sem_post(all->sem_stop);
		return ;
	}
	sem_post(all->sem_stop);
	sem_wait(all->sem_output);
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
	if (action == DEAD)
		printf("%-5zu %2d died\n", time_now(philo->start_time), philo->index);
	sem_post(all->sem_output);
}
