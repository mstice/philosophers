/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:45:32 by mtice             #+#    #+#             */
/*   Updated: 2025/11/13 18:29:37 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//-----------------------------------------------------------------------------
//initialises t_data struct
void	init_data(t_data *all)
{
	all->philos = NULL;
	all->n_philo = 0;
	all->to_die = 0;
	all->to_eat = 0;
	all->to_sleep = 0;
	all->must_eat = 0;
	all->stop = false;
	pthread_mutex_init(&(all->m_stop), NULL);
	pthread_mutex_init(&(all->m_output), NULL);
	pthread_mutex_init(&(all->m_meals), NULL);
	all->m_cutlery = NULL;
}

//-----------------------------------------------------------------------------
//initialises m_cutlery, which is an array of mutexes
//each member represents a fork, and there are as many forks as nbr of philos
int	init_forks(t_data *all)
{
	pthread_mutex_t	*m_cutlery;
	int				i;

	m_cutlery = malloc(sizeof(pthread_mutex_t) * all->n_philo);
	if (!m_cutlery)
		return (ft_putendl_fd(ERR_MALLOC, 2), 1);
	i = -1;
	while (++i < all->n_philo)
		pthread_mutex_init(&m_cutlery[i], NULL);
	all->m_cutlery = m_cutlery;
	return (0);
}

//-----------------------------------------------------------------------------
//initialises the t_philo struct
int	init_philos(t_data *all)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * (all->n_philo + 1));
	if (!philos)
		ft_putendl_fd(ERR_MALLOC, 2);
	i = -1;
	while (++i < all->n_philo)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			ft_putendl_fd(ERR_MALLOC, 2);
		philos[i]->index = i + 1;
		philos[i]->start_time = time_ms();
		philos[i]->last_meal = time_ms();
		philos[i]->meals = 0;
		philos[i]->all = all;
		philos[i]->forks.left_f = &(all->m_cutlery[i]);
		if (i == 0)
			philos[i]->forks.right_f = &(all->m_cutlery[all->n_philo - 1]);
		else
			philos[i]->forks.right_f = &(all->m_cutlery[i - 1]);
	}
	philos[all->n_philo] = NULL;
	return (all->philos = philos, 0);
}
