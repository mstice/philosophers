/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:25:21 by mtice             #+#    #+#             */
/*   Updated: 2025/11/13 18:21:33 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include "macros.h"

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc //free
# include <unistd.h> //write //usleep
# include <sys/time.h> //gettimeofday 
# include <pthread.h> //pthread_create //p_thread_detach //pthread_join //etc
# include <limits.h>
# include <stdbool.h>

//init_utils.c
void	init_data(t_data *all);
int		init_philos(t_data *all);
int		init_forks(t_data *all);

//input_check.c
int		parse_input(int argc, char *argv[], t_data *all);

//routines.c
int		start_dinner(t_data *all);

//routine_utils.c
void	stop(t_data *all);
bool	alive(t_data *all);
bool	enough(t_data *all);
void	print_output(t_data *all, t_philo *philo, t_state action);
void	pick_up_forks(t_data *all, t_philo *philo);

//utils.c
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
long	ft_atol(const char *s);
int		ft_isdigit(char c);

//time_utils.c
time_t	time_now(time_t start_time);
time_t	time_ms(void);
void	ms_sleep(size_t ms);
void	start_delay(time_t start_time);
void	assign_start_time(t_data *all);

//free_utils.c
void	free_data(t_data *all);

#endif
