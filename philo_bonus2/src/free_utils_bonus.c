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
	sem_unlink("cutlery");
	sem_close(all->sem_cutlery);
	sem_unlink("output");
	sem_close(all->sem_output);
	sem_unlink("meals");
	sem_close(all->sem_meals);
}

static void	free_philos(t_data *all)
{
	int	i;

	i = 0;
	while (i < all->n_philo)
		free(all->philos[i++]);
	free(all->philos);
}

void	ft_exit(t_data *all, int exit_code)
{
	// sem_unlink("cutlery");
	// sem_close(all->sem_cutlery);
	// sem_unlink("output");
	// sem_close(all->sem_output);
	// sem_unlink("meals");
	// sem_close(all->sem_output);
	(void)all;
	exit(exit_code);
}

static void	wait_children(t_data *all)
{
	int	i;

	i = -1;
	while (++i < all->n_philo)
	{
		if (all->pids[i] == waitpid(-1, NULL, 0))
		{
			if (errno == ECHILD)
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
