/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:37:28 by mtice             #+#    #+#             */
/*   Updated: 2025/10/21 16:04:11 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(t_data *all, char *argv[])
{
	int		j;
	long	n;
	
	j = 1;
	while (argv && argv[j] != NULL)
	{
		n = ft_atol(argv[j]);
		if (n <= 0 || n > INT_MAX)
			return (ft_putstr_fd(ARGS, 2), 1);
		else if (j == 1)
			all->n_philo = n;
		else if (j == 2)
			all->tdie = n;
		else if (j == 3)
			all->teat = n;
		else if (j == 4)
			all->tsleep = n;
		else if (j == 5)
			all->must_eat = n;
		j++;
	}
	return (0);
}

//------------------------------------------------------------------------------
//checks if input is correct
int	input_check(int argc, char *argv[])
{
	if (argc < 5)
		return (ft_putendl_fd("Insufficient args!", 2), ft_putstr_fd(USAGE, 2), 1);
	else if (argc > 6)
		return (ft_putendl_fd("Too many args!", 2), ft_putstr_fd(USAGE, 2), 1);
	(void)argv; //TODO: check through argv to check all strings are numbers
	return (0);
}
