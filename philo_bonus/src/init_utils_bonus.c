/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:45:32 by mtice             #+#    #+#             */
/*   Updated: 2025/11/11 11:53:05 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//-----------------------------------------------------------------------------
//initialises the t_philo struct
static int	init_philos(t_data *all)
{
	int		i;

	all->philos = malloc(sizeof(t_philo *) * (all->n_philo + 1));
	if (!all->philos)
		ft_putendl_fd(ERR_MALLOC, 2);
	i = -1;
	while (++i < all->n_philo)
	{
		all->philos[i] = malloc(sizeof(t_philo) * 1);
		if (!all->philos[i])
			ft_putendl_fd(ERR_MALLOC, 2);
		all->philos[i]->index = i + 1;
		all->philos[i]->start_time = time_ms();
		all->philos[i]->last_meal = time_ms();
		all->philos[i]->meals = 0;
		all->philos[i]->all = all;
	}
	all->philos[all->n_philo] = NULL;
	return (0);
}

//-----------------------------------------------------------------------------
//initialises the array that will store the pids of the children
static int	init_pids(t_data *all)
{
	int	i;

	all->pids = malloc(sizeof(pid_t) * all->n_philo);
	if (!all->pids)
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	i = -1;
	while (++i < all->n_philo)
		all->pids[i] = 0;
	return (0);
}

//-----------------------------------------------------------------------------
//opens semaphores and checks for opening problems
static int	init_sems(t_data *all)
{
	all->sem_cutlery
		= sem_open("/cutlery", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR,
			all->n_philo);
	if (all->sem_cutlery == SEM_FAILED)
		return (sem_error(all));
	all->sem_output
		= sem_open("/output", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (all->sem_output == SEM_FAILED)
		return (sem_error(all));
	all->sem_meals
		= sem_open("/meals", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (all->sem_meals == SEM_FAILED)
		return (sem_error(all));
	return (0);
}

//-----------------------------------------------------------------------------
//checks which type of error ocurred when SEM_FAILED was detected
//if EEXIST, destroys semaphores and re-initialises them
int	sem_error(t_data *all)
{
	if (errno == EEXIST)
	{
		destroy_sems(all);
		init_sems(all);
		return (0);
	}
	else
	{
		ft_putstr_fd(ERR_SEM_OPEN, 2);
		return (1);
	}
}

//-----------------------------------------------------------------------------
int	init_all(t_data *all)
{
	if (init_philos(all))
		return (1);
	else if (init_pids(all))
		return (1);
	else if (init_sems(all))
		return (1);
	return (0);
}
