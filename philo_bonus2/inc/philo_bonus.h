/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:25:21 by mtice             #+#    #+#             */
/*   Updated: 2025/11/10 20:30:58 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "structs_bonus.h"
# include "macros_bonus.h"

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc //free //exit
# include <unistd.h> //write //usleep
# include <sys/time.h> //gettimeofday 
# include <pthread.h> //pthread_create //p_thread_detach //pthread_join //etc
# include <limits.h>
# include <stdbool.h>
# include <sys/types.h> //fork
# include <signal.h> //kill
# include <sys/wait.h> //waitpid
# include <semaphore.h> //sem_open, sem_close, sem_wait, sem_unlink, sem_post
# include <fcntl.h>
# include <errno.h>

//init_utils.c
int		init_data(t_data *all);
int		init_all(t_data *all);

//input_check.c
int	parse_input(int argc, char *argv[], t_data *all);

//dinner.c
int	start_dinner(t_data *all);

//dinner_utils.c
bool	alive(t_data *all, sem_t **meals, t_philo *philo);
bool	enough_meals(t_data *all, sem_t **meals, t_philo *philo);
void	kill_all(t_data *all);
void	print_output(t_data *all, sem_t **meals, t_philo *philo, t_state action);

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
void	free_all(t_data *all);

#endif
