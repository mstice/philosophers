/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:20:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/13 18:29:35 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//-----------------------------------------------------------------------------
static void	destroy_m_cutlery(t_data *all)
{
	int	i;

	i = -1;
	while (++i < all->n_philo)
		pthread_mutex_destroy(&(all->m_cutlery[i]));
	free(all->m_cutlery);
}

//-----------------------------------------------------------------------------
static void	free_philos(t_data *all)
{
	int	i;

	i = 0;
	while (i < all->n_philo)
		free(all->philos[i++]);
	free(all->philos);
}

//-----------------------------------------------------------------------------
void	free_all(t_data *all)
{
	pthread_mutex_destroy(&(all->m_stop));
	destroy_m_cutlery(all);
	pthread_mutex_destroy(&(all->m_output));
	pthread_mutex_destroy(&(all->m_meals));
	free_philos(all);
}
