/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:37:28 by mtice             #+#    #+#             */
/*   Updated: 2025/10/27 18:58:15 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//-----------------------------------------------------------------------------
//parses the argv inputs into the t_data struct
static int	update_all(t_data *all, char *argv[])
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

//-----------------------------------------------------------------------------
//checks if an arg contains only digits
static int	only_digits(char *argv[])
{
	int	j;
	int	i;

	j = 1;
	while (argv[j] != NULL)
	{
		i = 0;
		while (argv[j][i] != '\0')
		{
			if (ft_isdigit(argv[j][i]))
				i++;
			else
				return (ft_putstr_fd(ERR_ARGS, 2), 1);
		}
		j++;
	}
	return (0);
}

//------------------------------------------------------------------------------
//checks correct number of args
static int	input_check(int argc)
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
	return (0);
}

//-----------------------------------------------------------------------------
int	parse_input(int argc, char *argv[], t_data *all)
{
	if (input_check(argc))
		return (1);
	if (only_digits(argv))
		return (1);
	if (update_all(all, argv))
		return (1);
	return (0);
}
