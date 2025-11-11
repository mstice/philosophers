/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:41:40 by mtice             #+#    #+#             */
/*   Updated: 2025/11/11 11:53:08 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//-----------------------------------------------------------------------------
//checks whether a philo is alive
bool	alive(t_data *all, sem_t **meals, t_philo *philo)
{
	bool	ret;

	sem_wait(*meals);
	if (time_ms() - philo->last_meal >= all->to_die)
		ret = false;
	else
		ret = true;
	sem_post(*meals);
	return (ret);
}

//-----------------------------------------------------------------------------
//returns true if philo has consumed enough meals
bool	enough_meals(t_data *all, sem_t **meals, t_philo *philo)
{
	bool	ret;

	if (all->must_eat == 0)
		return (false);
	sem_wait(*meals);
	if (philo->meals >= all->must_eat)
		ret = true;
	else
		ret = false;
	sem_post(*meals);
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
void	print_output(t_data *all, sem_t **meals, t_philo *philo, t_state action)
{
	if (action != THINK && action != FORK && action != EAT && action != SLEEP
		&& action != DEAD)
		return ;
	sem_wait(&(all->sem_output));
	if (alive(all, meals, philo))
		printf("%-5zu %2d ", time_now(philo->start_time), philo->index);
	if (action == THINK && alive(all, meals, philo))
		printf("is thinking\n");
	else if (action == FORK && alive(all, meals, philo))
		printf("has taken a fork\n");
	else if (action == EAT && alive(all, meals, philo))
		printf("is eating\n");
	else if (action == SLEEP && alive(all, meals, philo))
		printf("is sleeping\n");
	else if (action == DEAD && !alive(all, meals, philo))
		printf("%-5zu %2d died\n", time_now(philo->start_time), philo->index);
	sem_post(&(all->sem_output));
}
