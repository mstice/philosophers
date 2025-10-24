/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:25:21 by mtice             #+#    #+#             */
/*   Updated: 2025/10/23 11:35:09 by mtice            ###   ########.fr       */
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

//input_check.c
int		input_check(int argc, char *argv[]);
int		parse_input(t_data *all, char *argv[]);
int		create_philos(t_data *all);

//threads.c
int		start_dinner(t_data *all);

//utils.c
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
long	ft_atol(const char *s);

//time_utils.c
time_t	start_time(void);
time_t	time_now(time_t start_time);

//free_utils.c
void	free_data(t_data *all);

#endif
