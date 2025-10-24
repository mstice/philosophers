/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:37:28 by mtice             #+#    #+#             */
/*   Updated: 2025/10/23 14:32:41 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_data *all)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * (all->n_philo + 1));
	i = -1;
	while (++i < all->n_philo)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		philos[i]->index = i + 1;
		philos[i]->n_philo = all->n_philo;
		philos[i]->to_die = all->to_die;
		philos[i]->to_eat = all->to_eat;
		philos[i]->to_sleep = all->to_sleep;
		philos[i]->must_eat = all->must_eat;
		philos[i]->start_time = 0;
		philos[i]->last_meal = 0;
		philos[i]->meals = 0;
		philos[i]->alive = true;
		pthread_mutex_init(&(philos[i]->output), NULL);
		pthread_mutex_init(&(philos[i]->r_fork), NULL);
		pthread_mutex_init(&(philos[i]->l_fork), NULL);
		pthread_mutex_init(&(philos[i]->state), NULL);
	}
	philos[all->n_philo] = NULL;
	return (all->philos = philos, 0);
}

int	parse_input(t_data *all, char *argv[])
{
	int		j;
	long	n;

	j = 1;
	while (argv && argv[j] != NULL)
	{
		n = ft_atol(argv[j]);
		if (n <= 0 || n > INT_MAX)
			return (ft_putstr_fd(ERR_ARGS, 2), 1);
		else if (j == 1)
			all->n_philo = n;
		else if (j == 2)
			all->to_die = n;
		else if (j == 3)
			all->to_eat = n;
		else if (j == 4)
			all->to_sleep = n;
		else if (j == 5)
			all->must_eat = n;
		j++;
	}
	return (0);
}

//------------------------------------------------------------------------------
//checks if input is correct
//TODO: check through argv to check all strings are numbers
int	input_check(int argc, char *argv[])
{
	if (argc < 5)
		return (ft_putendl_fd("Insufficient args!", 2),
			ft_putendl_fd("Usage: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] (optional) \
[number_of_times_each_philosopher_must_eat]", 2), 1);
	else if (argc > 6)
		return (ft_putendl_fd("Too many args!", 2),
			ft_putendl_fd("Usage: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] (optional) \
[number_of_times_each_philosopher_must_eat]", 2), 1);
	(void)argv;
	return (0);
}
