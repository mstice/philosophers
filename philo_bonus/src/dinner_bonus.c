/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:15:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/13 17:08:45 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//-----------------------------------------------------------------------------
//thread that observes if children (philos) have exited
//if a philo has died, thread kills all children that are still alive
//once all philos have exited thread ends
static void	*waiter_routine(void *arg)
{
	t_data	*all;
	int		i;
	int		wstatus;

	all = (t_data *)arg;
	start_delay(all->all_start);
	while (errno != ESRCH)
	{
		i = 0;
		while (i < all->n_philo && errno != ESRCH)
		{
			if (waitpid(all->pids[i], &wstatus, WNOHANG) != 0)
			{
				if (WEXITSTATUS(wstatus) == ENOUGH)
					kill(all->pids[i], SIGKILL);
				else if (WEXITSTATUS(wstatus) == DEAD)
					return (print_output(all, all->philos[i], DEAD),
						kill_all(all), NULL);
			}
			i++;
		}
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
//special routine for 1 philosopher 1 fork case
static void	alone_routine(t_data *all, t_philo *which_philo)
{
	start_delay(all->all_start);
	sem_wait(all->sem_cutlery);
	print_output(all, which_philo, FORK);
	ms_sleep(all->to_die);
	sem_post(all->sem_cutlery);
	exit(DEAD);
}

//-----------------------------------------------------------------------------
static void	philosopher_routine(t_data *all, t_philo *which_philo)
{
	if (all->n_philo == 1)
		(alone_routine(all, which_philo));
	start_delay(all->all_start);
	if (which_philo->index % 2)
	{
		print_output(all, which_philo, THINK);
		usleep(all->to_eat * 1000);
	}
	while (alive(all, which_philo))
	{
		(sem_wait(all->sem_cutlery), print_output(all, which_philo, FORK));
		(sem_wait(all->sem_cutlery), print_output(all, which_philo, FORK));
		which_philo->last_meal = time_ms();
		which_philo->meals++;
		(print_output(all, which_philo, EAT), ms_sleep(all->to_eat));
		(sem_post(all->sem_cutlery), sem_post(all->sem_cutlery));
		if (enough_meals(all, which_philo))
			exit(ENOUGH);
		(print_output(all, which_philo, SLEEP), ms_sleep(all->to_sleep));
	}
	exit(EXIT_FAILURE);
}

//-----------------------------------------------------------------------------
int	start_dinner(t_data *all)
{
	int			i;
	pid_t		pid;
	pthread_t	waiter;

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
