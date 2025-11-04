/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:24:19 by mtice             #+#    #+#             */
/*   Updated: 2025/11/04 14:49:22 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_usleep(size_t ms)
{
	size_t	start;

	start = time_ms();
	while (time_ms() - start < ms)
		usleep (100);
}

void	sim_start_delay(time_t start_time)
{
	while (time_ms() < start_time)
		continue ;
}
