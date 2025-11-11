/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:15:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/10 20:48:03 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	end = 0;

//TODO: remove forbidden function getpid
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
		kill(all->pids[i], SIGKILL);
		i++;
	}
}

static void	think_routine(t_data *all, t_philo *philo, bool silent)
{
	time_t	time_to_think;

	if (!no_deaths(all))
		return ;
	sem_wait(&(all->sem_meals));
	time_to_think
		= (all->to_die - (time_ms() - philo->last_meal) - all->to_eat)
		/ 2;
	sem_post(&(all->sem_meals));
	if (time_to_think <= 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!silent)
		print_output(all, philo, THINK);
	sem_wait(&(all->sem_status));
	// all->status[philo->index - 1] = HUNGRY;
	sem_post(&(all->sem_status));
	ms_sleep(time_to_think);
}

static void	*waiter_routine(void *arg)
{
	t_data	*all;
	int		i;

	all = (t_data *)arg;
	// start_delay(all->all_start);
	while (42)
	{
		i = 0;
		while (i < all->n_philo)
		{
			if (time_ms() - all->philos[i]->last_meal >= all->to_die)
			{
				print_output(all, all->philos[i], DEAD);
				death_or_full(all);
				kill_all(all);
				sem_wait(&(all->sem_status));
				memset(all->status, DEAD, all->n_philo);
				end = 1;
				// all->status[i] = DEAD;
				sem_post(&(all->sem_status));
				return (NULL);
			}
			i++;
		}
		if (all_eat(all))
			return (NULL);
	}
	return (NULL);
}

// static int	left(t_data *all, int i)
// {
// 	return((i - 1 + all->n_philo) % all->n_philo);
// }
//
// static int	right(t_data *all, int i)
// {
// 	return ((i + 1) % all->n_philo);
// }
//
// static int	test(t_data *all, int i)
// {
// 	if (all->status[i] == HUNGRY && all->status[left(all, i)] != EAT && all->status[right(all, i)] != EAT)
// 		return (1);
// 	return (0);
// }

static void	alone_routine(t_data *all, t_philo *which_philo)
{
	start_delay(all->all_start);
	sem_wait(&(all->cutlery[which_philo->index - 1]));
	print_output(all, which_philo, FORK);
	ms_sleep(all->to_die);
	sem_post(&(all->cutlery[which_philo->index - 1]));
	exit(1);
}

//TODO: LONE PHILO ROUTINE
static void	philosopher_routine(t_data *all, t_philo *which_philo)
{
	printf("hi I am philosopher %d\n", which_philo->index);
	if (all->n_philo == 1)
		alone_routine(all, which_philo);
	start_delay(all->all_start);
	// if (which_philo->index % 2)
	// 	think_routine(all, which_philo, true);
	while (no_deaths(all))
	{
		// test(all, which_philo->index - 1);
		sem_wait(&(all->cutlery[which_philo->index - 1]));
		print_output(all, which_philo, FORK);
		if (which_philo->index == 1)
			sem_wait(&(all->cutlery[all->n_philo - 1]));
		else
			sem_wait(&(all->cutlery[which_philo->index - 2]));
		print_output(all, which_philo, FORK);

		sem_wait(&(all->sem_meals));
		which_philo->last_meal = time_ms();
		sem_wait(&(all->sem_status));
		// all->status[which_philo->index - 1] = EAT;
		sem_post(&(all->sem_status));
		sem_post(&(all->sem_meals));
		print_output(all, which_philo, EAT);
		ms_sleep(all->to_eat);

		sem_post(&(all->cutlery[which_philo->index - 1]));
		if (which_philo->index == 1)
			sem_post(&(all->cutlery[all->n_philo - 1]));
		else
			sem_post(&(all->cutlery[which_philo->index - 2]));
		print_output(all, which_philo, SLEEP);
		sem_wait(&(all->sem_status));
		// all->status[which_philo->index - 1] = SLEEP;
		sem_post(&(all->sem_status));
		ms_sleep(all->to_sleep);
		think_routine(all, which_philo, false);
		// if (sem_wait(&(all->sem_cutlery)) < 0)
		//  		perror("sem_wait"), exit(1);
		// print_output(all, which_philo, FORK);
		// sem_wait(&(all->sem_cutlery));
		// print_output(all, which_philo, FORK);
		// sem_wait(&(all->sem_meals));
		// which_philo->last_meal = time_ms();
		// sem_wait(&(all->sem_status));
		// all->status[which_philo->index - 1] = EAT;
		// sem_post(&(all->sem_status));
		// sem_post(&(all->sem_meals));
		// print_output(all, which_philo, EAT);
		// ms_sleep(all->to_eat);
		// if (sem_post(&(all->sem_cutlery)) < 0)
		// 	perror("sem_post"), exit(1);
		// sem_post(&(all->sem_cutlery));
		// think_routine(all, which_philo, false);
		// // sem_wait(&some_semaphore);
		// ms_sleep(all->to_die);
		// // if (all->stop && printf("philo:%d ret:%d\n", which_philo->index, 0))
		// // 	exit(0);
		// // sleep(5);
		// printf("philo:%d ret:%d\n", which_philo->index, 1);
		// // sem_post(&some_semaphore);
		// exit(1);
	}
	exit(1);
}

int	start_dinner(t_data *all)
{
	pthread_t	waiter;
	int			i;
	pid_t		pid;

	assign_start_time(all);
	// if (pthread_create(&waiter, NULL, &waiter_routine, all))
	// 	return (ft_putstr_fd(ERR_CREATE, 2), 1);
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
