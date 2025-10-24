/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:57:39 by mtice             #+#    #+#             */
/*   Updated: 2025/10/23 14:34:25 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_data(t_data *all)
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

int	main(int argc, char *argv[])
{
	t_data	all;

	init_data(&all);
	if (input_check(argc, argv) || parse_input(&all, argv))
		return (1);
	if (create_philos(&all))
		return (free_data(&all), 1);
	if (start_dinner(&all))
		return (free_data(&all), 1);
	free_data(&all);
	return (0);
}
