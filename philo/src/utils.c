/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:50:27 by mtice             #+#    #+#             */
/*   Updated: 2025/10/23 10:31:08 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putendl_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
	return (i);
}

long	ft_atol(const char *s)
{
	long	i;
	long	number;
	long	sign;

	i = 0;
	number = 0;
	sign = 1;
	while ((s[i] == ' ') || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
			number = number * 10 + (s[i] - '0');
		else
			break ;
		i++;
	}
	return (number * sign);
}
