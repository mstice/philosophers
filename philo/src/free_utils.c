/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:20:30 by mtice             #+#    #+#             */
/*   Updated: 2025/10/23 11:55:32 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_philos(t_data *all)
{
	int	i;

	i = 0;
	while (i < all->n_philo)
		free(all->philos[i++]);
	free(all->philos);
}

void	free_data(t_data *all)
{
	int	i;

	i = 0;
	while (all->philos[i] != NULL)
	{
		pthread_mutex_destroy(&(all->philos[i]->output));
		pthread_mutex_destroy(&(all->philos[i]->l_fork));
		pthread_mutex_destroy(&(all->philos[i]->r_fork));
		pthread_mutex_destroy(&(all->philos[i]->state));
		i++;
	}
	free_philos(all);
}
