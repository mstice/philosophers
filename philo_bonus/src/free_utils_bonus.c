/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:20:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/06 18:33:47 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static void	destroy_cutlery(t_data *all)
// {
// 	int	i;
//
// 	i = -1;
// 	while (++i < all->n_philo)
// 		sem_destroy(&cutlery[i]);
// 	free(all->cutlery);
// }

static void	free_philos(t_data *all)
{
	int	i;

	i = 0;
	while (i < all->n_philo)
		free(all->philos[i++]);
	free(all->philos);
}

static void	wait_children(t_data *all)
{
	while (pid == waitpid(-1, NULL, 0))
	{
		if (errno == ECHILD)
			break;
	}
	printf("All children exited\n");
}

void	free_data(t_data *all)
{
	// destroy_cutlery(all);
	wait_children(all);
	free(all->pids);
	free_philos(all);
}
