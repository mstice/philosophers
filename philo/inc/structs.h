/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:09:38 by mtice             #+#    #+#             */
/*   Updated: 2025/10/28 12:08:49 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <time.h>

typedef enum e_state	t_state;
typedef struct s_forks	t_forks;
typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef enum e_state
{
	THINK,
	FORK,
	EAT,
	SLEEP,
	DEAD
}			t_state;

typedef struct s_forks
{
	pthread_mutex_t	*right_f;
	pthread_mutex_t	*left_f;
}				t_forks;

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	time_t			start_time;
	time_t			last_meal;
	int				meals;
	t_forks			forks;
	t_data			*all;
}				t_philo;

typedef struct s_data
{
	t_philo			**philos;
	int				n_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				must_eat;
	bool			stop;
	pthread_mutex_t	sim_stop;
	pthread_mutex_t	state;
	pthread_mutex_t	meals;
	pthread_mutex_t	*cutlery;
	pthread_mutex_t	over;
}				t_data;

#endif
