/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:09:38 by mtice             #+#    #+#             */
/*   Updated: 2025/11/18 20:06:33 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include <pthread.h>
# include <stdbool.h>
# include <time.h>
# include <semaphore.h>

typedef enum e_state	t_state;
typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef enum e_state
{
	THINK,
	FORK,
	EAT,
	SLEEP,
	ENOUGH,
	DEAD,
}			t_state;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_t		pwaiter;
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
	time_t			all_start;
	pid_t			*pids;
	sem_t			*sem_cutlery;
	sem_t			*sem_output;
	sem_t			*sem_meals;
	sem_t			*sem_stop;
	bool			stop;
}				t_data;

#endif
