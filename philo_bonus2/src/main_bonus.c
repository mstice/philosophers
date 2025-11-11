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

int	main(int argc, char *argv[])
{
	t_data	all;

	if (init_data(&all) || parse_input(argc, argv, &all))
		return (1);
	else if (init_all(&all))
		return (free_all(&all), 1);
	else if (printf("starting dinner\n") && start_dinner(&all))
		return (free_all(&all), 1);
	free_all(&all);
	printf("dinner is over!\n");
	return (0);
}
