/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:09:38 by mtice             #+#    #+#             */
/*   Updated: 2025/10/21 16:08:42 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <pthread.h>

typedef enum	e_state
{
	UNDEFINED,
	EAT,
	THINK,
	SLEEP,
	DEAD
}				t_state;

typedef struct	s_philo
{
	t_state		state;
}				t_philo;

typedef struct	s_data
{
	t_philo		*philo;
	int				n_philo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				must_eat;
	pthread_mutex_t	mutex;
}				t_data;

#endif
