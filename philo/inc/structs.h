/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:09:38 by mtice             #+#    #+#             */
/*   Updated: 2025/10/23 14:32:11 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <time.h>

typedef enum e_state
{
	UNDEFINED,
	SLEEPING,
	HUNGRY,
	EATING,
	DEAD
}				t_state;

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	int				n_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				must_eat;
	time_t			start_time;
	time_t			last_meal;
	int				meals;
	int				alive;
	pthread_mutex_t	output;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	state;
}				t_philo;

typedef struct s_data
{
	t_philo			**philos;
	int				n_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				must_eat;
}				t_data;

#endif
