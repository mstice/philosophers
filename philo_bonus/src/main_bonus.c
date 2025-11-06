/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:57:35 by mtice             #+#    #+#             */
/*   Updated: 2025/11/06 19:19:39 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	all;

	init_data(&all);
	if (parse_input(argc, argc, &all))
		return (1);
	else if (init_philos(&all) || init_cutlery(&all))
			return (free_data(&all), 1);
	else if (start_dinner(&all))
			return (free_data(&all), 1);
	free_data(&all);
	return (0);
}
