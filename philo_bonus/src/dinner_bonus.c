/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:15:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/07 13:59:03 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_all(t_data *all)
{
	int	i;

	i = -1;
	while (++i < all->n_philo)
	{
		if (all->pids[i] == getpid())
		{
			printf("You just tried to kill the parent!\n");
			return ;
		}
		kill(all->pids[i], SIGTERM);
		i++;
	}
}

static void	*waiter_routine(void *arg)
{
	t_data	*all;
	int		i;

	all = (t_data *)arg;
	while (42)
	{
		i = 0;
		while (i < all->n_philo)
		{
			if (time_ms() - all->philos[i]->last_meal >= all->to_die)
			{
				print_state(all, all->philos[i], DEAD);
				death_or_full(all);
				kill_all(all);
				return (NULL);
			}
			i++;
		}
		if (all_eat(all))
			return (NULL);
	}
	return (NULL);
}

static void	philosopher_routine(t_data *all, t_philo *which_philo)
{
	(void)all;
	// start_delay(all->all_start);
	printf("hi I am philosopher %d\n", which_philo->index);
	// sem_wait(&some_semaphore);
	ms_sleep(all->to_die);
	if (all->stop && printf("philo:%d ret:%d\n", which_philo->index, 0))
		exit(0);
	sleep(1000);
	printf("philo:%d ret:%d\n", which_philo->index, 1);
	// sem_post(&some_semaphore);
	exit(1);
}

int	start_dinner(t_data *all)
{
	pthread_t	waiter;
	int			i;
	pid_t		pid;

	assign_start_time(all);
	i = -1;
	while (++i < all->n_philo)
	{
		pid = fork();
		if (pid < 0)
			return (ft_putstr_fd(ERR_FORK, 2), 1);
		else if (pid > 0)
			all->pids[i] = pid;
		else if (pid == 0)
			philosopher_routine(all, all->philos[i]);
	}
	if (pthread_create(&waiter, NULL, &waiter_routine, all))
		return (ft_putstr_fd(ERR_CREATE, 2), 1);
	if (pthread_join(waiter, NULL))
		return (ft_putstr_fd(ERR_JOIN, 2), 1);
	return (0);
}
