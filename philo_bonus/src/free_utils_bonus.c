/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:20:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/18 20:06:34 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//-----------------------------------------------------------------------------
//unlinks and destroys semaphores
void	destroy_sems(t_data *all)
{
	sem_unlink("/cutlery");
	sem_close(all->sem_cutlery);
	sem_unlink("/output");
	sem_close(all->sem_output);
	sem_unlink("/meals");
	sem_close(all->sem_meals);
	sem_unlink("/stop");
	sem_close(all->sem_stop);
}

//-----------------------------------------------------------------------------
//frees the philo array
static void	free_philos(t_data *all)
{
	int	i;

	i = 0;
	while (i < all->n_philo)
		free(all->philos[i++]);
	free(all->philos);
}

//-----------------------------------------------------------------------------
//waits for all children to finish executing
static void	wait_children(t_data *all)
{
	int	i;

	i = -1;
	while (++i < all->n_philo)
	{
		if (all->pids[i] == waitpid(-1, NULL, 0))
		{
			if (errno == ECHILD)
				break ;
		}
	}
}

//-----------------------------------------------------------------------------
void	free_all(t_data *all)
{
	destroy_sems(all);
	wait_children(all);
	free(all->pids);
	free_philos(all);
}

//-----------------------------------------------------------------------------
void	ft_exit(t_data *all, pthread_t *pwaiter, int exit_code)
{
	if (pthread_join(*pwaiter, NULL))
	{
		ft_putstr_fd(ERR_JOIN, 2);
		exit_code = EXIT_FAILURE;
	}
	destroy_sems(all);
	free(all->pids);
	free_philos(all);
	exit(exit_code);
}
