/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:57:35 by mtice             #+#    #+#             */
/*   Updated: 2025/11/10 20:31:14 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
//-----------------------------------------------------------------------------
//initialises t_data struct
static int	init_data(t_data *all)
{
	all->philos = NULL;
	all->n_philo = 0;
	all->to_die = 0;
	all->to_eat = 0;
	all->to_sleep = 0;
	all->must_eat = 0;
	all->pids = NULL;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	all;

	init_data(&all);
	if (parse_input(argc, argv, &all))
		return (1);
	else if (init_all(&all))
		return (free_all(&all), 1);
	if (start_dinner(&all))
		return (free_all(&all), 1);
	free_all(&all);
	return (0);
}
