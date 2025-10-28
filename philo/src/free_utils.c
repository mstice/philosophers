/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:20:30 by mtice             #+#    #+#             */
/*   Updated: 2025/10/28 12:06:22 by mtice            ###   ########.fr       */
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

	i = -1;
	while (++i < all->n_philo)
		pthread_mutex_destroy(&(all->cutlery[i]));
	free(all->cutlery);
	pthread_mutex_destroy(&(all->meals));
	pthread_mutex_destroy(&(all->state));
	free_philos(all);
}
