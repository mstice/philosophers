/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:45:32 by mtice             #+#    #+#             */
/*   Updated: 2025/11/06 19:19:37 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//-----------------------------------------------------------------------------
//initialises t_data struct
//TODO: remove stop
void	init_data(t_data *all)
{
	all->philos = NULL;
	all->n_philo = 0;
	all->to_die = 0;
	all->to_eat = 0;
	all->to_sleep = 0;
	all->must_eat = 0;
	all->pids = NULL;
	all->stop = false;
	sem_init(&(all->meals), 1, 1);
	sem_init(&(all->state), 1, 1);
	sem_init(&(all->sim_stop), 1, 1);
}

//-----------------------------------------------------------------------------
//initialises cutlery, which is an array of mutexes
//each member represents a fork, and there are as many forks as nbr of philos
//sem_init(sem_t *sem, int pshared, unsigned int value)
//value is whatever you want to initialise the semaphore to
//TODO: pshared should be non-zero so that the semaphore can be shared across processes
// int	init_cutlery(t_data *all)
// {
// 	int		i;
//
// 	all->cutlery = malloc(sizeof(sem_t) * all->n_philo);
// 	if (!all->cutlery)
// 		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
// 	i = -1;
// 	while (++i < all->n_philo)
// 	{
// 		if (sem_init(&(all->cutlery[i]), 1, 1) < 0) //fork the forks, value must be n_philo
// 			return (ft_putstr_fd(ERR_SEM_INIT, 2), 1);
// 	}
// 	return (0);
// }

//-----------------------------------------------------------------------------
//initialises the t_philo struct
static int	init_philos(t_data *all)
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
		// philos[i]->forks.left_f = &(all->cutlery[i]);
		// if (i == 0)
		// 	philos[i]->forks.right_f = &(all->cutlery[all->n_philo - 1]);
		// else
		// 	philos[i]->forks.right_f = &(all->cutlery[i - 1]);
	}
	philos[all->n_philo] = NULL;
	return (all->philos = philos, 0);
}

static int	init_pids(t_data *all)
{
	int	i;

	i = -1;
	all->pids = malloc(sizeof(pid_t) * all->n_philo);
	if (!all->pids)
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	while (++i < all->n_philo)
		all->pids[i] = 0;
	return (0);
}

// static int	init_status(t_data *all)
// {
// 	int	i;
//
// 	all->status = malloc(sizeof(t_state) * all->n_philo);
// 	if (!all->status)
// 		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
// 	i = -1;
// 	while (++i < all->n_philo)
// 		all->status[i] = HUNGRY;
// 	return (0);
// }

int	init_all(t_data *all)
{
	// if (init_cutlery(all))
	// 	return (1);
	if (init_philos(all))
		return (1);
	else if (init_pids(all))
		return (1);
	// else if (init_status(all))
	// 	return (1);
	sem_init(&(all->cutlery), 1, all->n_philo);
	return (0);
}
