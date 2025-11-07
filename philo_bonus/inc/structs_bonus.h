/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:09:38 by mtice             #+#    #+#             */
/*   Updated: 2025/11/06 18:30:46 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

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

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	time_t			start_time;
	time_t			last_meal;
	int				meals;
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
	pid_t			*pids;
	time_t			all_start;
	// bool			stop;
	sem_t			room;
	sem_t			*cutlery;
	sem_t			stop;
}				t_data;

#endif
