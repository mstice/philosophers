/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:15:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/18 20:06:37 by mtice            ###   ########.fr       */
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
					return (kill_all(all), NULL);
				else if (WEXITSTATUS(wstatus) == EXIT_FAILURE)
					return (ft_putstr_fd(ERR_EXIT, 2), kill_all(all), NULL);
			}
			i++;
		}
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
static void	*pwaiter_routine(void *arg)
{
	t_philo	*philo;
	t_data	*all;

	philo = (t_philo *)arg;
	all = philo->all;
	start_delay(all->all_start);
	while (42)
	{
		sem_wait(all->sem_meals);
		if (time_ms() - philo->last_meal >= all->to_die)
		{
			sem_post(all->sem_meals);
			print_output(all, philo, DEAD);
			sem_wait(all->sem_stop);
			all->stop = true;
			sem_post(all->sem_stop);
			return (NULL);
		}
		sem_post(all->sem_meals);
		sem_wait(all->sem_meals);
		if (all->must_eat > 0 && philo->meals >= all->must_eat)
		{
			sem_post(all->sem_meals);
			sem_wait(all->sem_stop);
			all->stop = true;
			sem_post(all->sem_stop);
			return (NULL);
		}
		sem_post(all->sem_meals);
		usleep(100);
		continue ;
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
//special routine for 1 philosopher 1 fork case
static void	alone_routine(t_data *all, t_philo *philo)
{
	start_delay(all->all_start);
	sem_wait(all->sem_cutlery);
	print_output(all, philo, FORK);
	ms_sleep(all->to_die);
	sem_post(all->sem_cutlery);
	ft_exit(all, &(philo->pwaiter), DEAD);
}

//-----------------------------------------------------------------------------
static void	philosopher_routine(t_data *all, t_philo *philo)
{
	if (pthread_create(&(philo->pwaiter), NULL, &pwaiter_routine, philo))
		(ft_putstr_fd(ERR_CREATE, 2), ft_exit(all, &(philo->pwaiter), EXIT_FAILURE));
	if (all->n_philo == 1)
		(alone_routine(all, philo));
	start_delay(all->all_start);
	if (philo->index % 2)
		(print_output(all, philo, THINK), usleep(all->to_eat * 1000));
	while (!enough_meals(all, philo))
	{
		(sem_wait(all->sem_cutlery), print_output(all, philo, FORK));
		(sem_wait(all->sem_cutlery), print_output(all, philo, FORK));
		if (!alive(all, philo))
			break ;
		(sem_wait(all->sem_meals), philo->last_meal = time_ms());
		(philo->meals++, sem_post(all->sem_meals));
		(print_output(all, philo, EAT), ms_sleep(all->to_eat));
		(sem_post(all->sem_cutlery), sem_post(all->sem_cutlery));
		(print_output(all, philo, SLEEP), ms_sleep(all->to_sleep));
		print_output(all, philo, THINK);
	}
	if (enough_meals(all, philo))
		ft_exit(all, &(philo->pwaiter), ENOUGH);
	ft_exit(all, &(philo->pwaiter), DEAD);
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
