/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:20:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/10 20:31:28 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	destroy_sems(t_data *all)
{
	int	i;

	i = -1;
	while (++i < all->n_philo)
	{
		sem_destroy(&(all->cutlery[i]));
		sem_destroy(&(all->status[i]));
	}
	free(all->cutlery);
	free(all->status);
	sem_destroy(&(all->sem_cutlery));
	sem_destroy(&(all->sem_meals));
	sem_destroy(&(all->sem_output));
	sem_destroy(&(all->sem_sim_stop));
	sem_destroy(&(all->sem_status));
}

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
	int	i;

	i = -1;
	while (++i < all->n_philo)
	{
		if (all->pids[i] == waitpid(-1, NULL, 0))
		{	if (errno == ECHILD)
				break;
		}
	}
	printf("All children exited\n");
}

void	free_all(t_data *all)
{
	destroy_sems(all);
	wait_children(all);
	free(all->pids);
	free_philos(all);
}
