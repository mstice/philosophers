/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:24:19 by mtice             #+#    #+#             */
/*   Updated: 2025/10/23 11:26:28 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	start_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_putstr_fd(ERR_TIME, 2);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

time_t	time_now(time_t start_time)
{
	struct	timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_putstr_fd(ERR_TIME, 2);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

// time_t	time_ms(struct timeval start_time)
// {
// 	struct timeval current;
//
// 	gettimeofday(&current, NULL);
// 	return ((current.tv_sec - start_time.tv_sec) * 1000 + (current.tv_usec - start_time.tv_usec) / 1000);
// }
//
// int	main(void)
// {
// 	time_t	start;
// 	time_t	end;
//
// 	start = time_ms();
// 	usleep(100 * 1000);
// 	end = get_time(start);
// 	printf("start: %zu, end %zu\n", start, end);
// 	return (0);
// }
