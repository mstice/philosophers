/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:24:19 by mtice             #+#    #+#             */
/*   Updated: 2025/11/07 13:59:04 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	time_now(time_t start_time)
{
	return (time_ms() - start_time);
}

time_t	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ms_sleep(size_t ms)
{
	size_t	start;

	start = time_ms();
	while (time_ms() - start < ms)
		usleep (100);
}

void	start_delay(time_t start_time)
{
	while (time_ms() < start_time)
		usleep(100);
}

void	assign_start_time(t_data *all)
{
	int	i;

	all->all_start = time_ms() + (all->n_philo * 2 * 10);
	i = -1;
	while (++i < all->n_philo)
	{
		all->philos[i]->start_time = all->all_start;
		all->philos[i]->last_meal = all->all_start;
	}
}
