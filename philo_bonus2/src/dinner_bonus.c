/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:15:30 by mtice             #+#    #+#             */
/*   Updated: 2025/11/11 11:53:08 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static void	think_routine(t_data *all, t_philo *philo, bool silent)
// {
// 	time_t	time_to_think;
//
// 	sem_wait(&(all->sem_meals));
// 	time_to_think
// 		= (all->to_die - (time_ms() - philo->last_meal) - all->to_eat)
// 		/ 2;
// 	sem_post(&(all->sem_meals));
// 	if (time_to_think <= 0)
// 		time_to_think = 0;
// 	if (time_to_think == 0 && silent == true)
// 		time_to_think = 1;
// 	// if (time_to_think > 600)
// 	// 	time_to_think = 200;
// 	if (!silent)
// 		print_output(all, philo, THINK);
// 	ms_sleep(time_to_think);
// }

static void	*waiter_routine(void *arg)
{
	t_data	*all;
	int		i;
	int		wstatus;

	all = (t_data *)arg;
	// all->sem_meals = sem_open("meals", O_CREAT, 0644, 1);
	// sem_t *output = sem_open("output", 0);
	start_delay(all->all_start);
	while (42)
	{
		i = 0;
		while (i < all->n_philo)
		{
			if (errno == ESRCH)
				return (NULL);
			if (waitpid(all->pids[i], &wstatus, WNOHANG) != 0)
			{
				if (WEXITSTATUS(wstatus) == ENOUGH)
					kill(all->pids[i], SIGKILL);
				else if (WEXITSTATUS(wstatus) == DEAD)
				{
					// print_output(all, &(all->sem_meals), &output, all->philos[i], DEAD);
					printf("%d: DIED\n", i + 1);
					kill_all(all);
					return (NULL);
				}
			}
			i++;
		}
	}
	return (NULL);
}

static void	alone_routine(t_data *all, sem_t **cutlery, sem_t **output, sem_t **meals, t_philo *which_philo)
{
	start_delay(all->all_start);
	sem_wait(*cutlery);
	print_output(all, meals, output, which_philo, FORK);
	ms_sleep(all->to_die);
	sem_post(*cutlery);
}

//TODO: FIX PICKING UP OF FORKS
static void	philosopher_routine(t_data *all, t_philo *which_philo)
{
	printf("hi I am philosopher %d\n", which_philo->index);
	sem_t	*cutlery = sem_open("cutlery", 0);
	sem_t	*output = sem_open("output", 0);
	all->sem_meals = sem_open("meals", O_CREAT, 0644, 1);
	sem_t *meals = all->sem_meals;
	if (all->n_philo == 1)
		(alone_routine(all, &cutlery, &output, &meals, which_philo), exit(EXIT_SUCCESS));
	start_delay(all->all_start);
	if (which_philo->index % 2)
		ms_sleep(all->to_eat);
	while (42)
	{
		(sem_wait(cutlery), print_output(all, &meals, &output, which_philo, FORK));
		(sem_wait(cutlery), print_output(all, &meals, &output, which_philo, FORK));
		which_philo->last_meal = time_ms();
		which_philo->meals++;
		(print_output(all, &meals, &output, which_philo, EAT), ms_sleep(all->to_eat));
		(sem_post(cutlery), sem_post(cutlery));
		if (enough_meals(all, &meals, which_philo))
			ft_exit(all, ENOUGH);
		(print_output(all, &meals, &output, which_philo, SLEEP), ms_sleep(all->to_sleep));
		if (!alive(all, &meals, which_philo))
			ft_exit(all, DEAD);
	}
	ft_exit(all, EXIT_FAILURE);
}

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
