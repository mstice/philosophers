/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:15:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/06 19:12:04 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(size_t i)
{
	state[i] = HUNGRY;
	printf("%zu is hungry\n", i);
	test(i);
	sem_wait(&cutlery[i]);
}

// static void	*waiter_routine(void *arg)
// {
// 	t_data	*all;
// 	int		i;
//
// 	all = (t_data *arg);
// 	while (42)
// 	{
// 		i = 0;
// 		while (i < all->n_philo)
// 		{
// 		}
// 	}
// }

int	start_dinner(t_data *all)
{
	// pthread_t	waiter;
	int			i;

	assign_start_time(all);
	// if (pthread_create(&waiter, NULL, &waiter_routine, all))
	// 	return (ft_putstr_fd(ERR_CREATE, 2), 1);
	//something there
	// if (pthread_join(waiter, NULL))
	// 	return (ft_putstr_fd(ERR_JOIN, 2), 1);
	return (0);
}
