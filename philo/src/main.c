/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:57:39 by mtice             #+#    #+#             */
/*   Updated: 2025/10/27 18:58:16 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	all;

	init_data(&all);
	if (input_check(argc, argv) || parse_input(&all, argv))
		return (1);
	if (init_philos(&all))
		return (free_data(&all), 1);
	if (start_dinner(&all))
		return (free_data(&all), 1);
	free_data(&all);
	return (0);
}
