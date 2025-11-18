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

////-----------------------------------------------------------------------------
////checks whether a philo is alive
//bool	alive(t_data *all, t_philo *philo)
//{
//	bool	ret;
//
//	sem_wait(all->sem_meals);
//	if (time_ms() - philo->last_meal >= all->to_die)
//		ret = false;
//	else
//		ret = true;
//	sem_post(all->sem_meals);
//	if (ret == false)
//		ft_exit(all, &(philo->pwaiter), DEAD);
//	return (ret);
//}
//
////-----------------------------------------------------------------------------
////returns true if philo has consumed enough meals
//bool	enough_meals(t_data *all, t_philo *philo)
//{
//	bool	ret;
//
//	if (all->must_eat == 0)
//		return (false);
//	sem_wait(all->sem_meals);
//	if (philo->meals >= all->must_eat)
//		ret = true;
//	else
//		ret = false;
//	sem_post(all->sem_meals);
//	if (ret == true)
//		ft_exit(all, &(philo->pwaiter), ENOUGH);
//	return (ret);
//}
//
//
int	dead_or_full(t_data *all, t_philo *philo)
{
	int	ret;

	ret = 0;
	sem_wait(all->sem_meals);
	if (time_ms() - philo->last_meal == all->to_die)
		ret = DEAD;
	else if (all->must_eat > 0 && philo->meals >= all->must_eat)
		ret = ENOUGH;
	sem_post(all->sem_meals);
	if (ret == DEAD)
		ft_exit(all, philo->pwaiter, DEAD);
	else if (ret == ENOUGH)
		ft_exit(all, philo->pwaiter, ENOUGH);
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
	if (action != DEAD)
		alive(all, philo);
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
