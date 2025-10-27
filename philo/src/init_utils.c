/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:45:32 by mtice             #+#    #+#             */
/*   Updated: 2025/10/27 18:58:16 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *all)
{
	all->philos = NULL;
	all->n_philo = 0;
	all->to_die = 0;
	all->to_eat = 0;
	all->to_sleep = 0;
	all->must_eat = 0;
	all->stop = false;
	pthread_mutex_init(&(all->state), NULL);
	pthread_mutex_init(&(all->meals), NULL);
	pthread_mutex_init(&(all->r_fork), NULL);
	pthread_mutex_init(&(all->l_fork), NULL);
}

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
		philos[i]->start_time = 0;
		philos[i]->last_meal = 0;
		philos[i]->meals = 0;
		philos[i]->all = all;
	}
	philos[all->n_philo] = NULL;
	return (all->philos = philos, 0);
}

int	init_forks(t_data *all)
{
	t_forks	**forks;
	int		i;

	forks = malloc(sizeof(t_forks *) * all->n_philo);
	if (!forks)
		ft_putendl_fd(ERR_MALLOC, 2);
	i = -1;
	while (++i < all->n_philo)
	{
		forks[i] = malloc(sizeof(t_forks) * 1);
		if (i - 1 == n_philo)
			pthread_mutex_init()
		pthread_mutex_init(&(forks[i]->left_f));
		pthread_mutex_init(&(forks[i]->right_f));
	}
}
