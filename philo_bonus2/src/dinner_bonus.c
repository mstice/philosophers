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
	sem_t	**meals;
	int		i;
	int		wstatus;

	all = (t_data *)arg;
	meals = all->sem_meals;
	meals[0] = sem_open("meals0", 0);
	meals[1] = sem_open("meals1", 0);
	meals[2] = sem_open("meals2", 0);
	meals[3] = sem_open("meals3", 0);
	meals[4] = sem_open("meals4", 0);
	start_delay(all->all_start);
	while (42)
	{
		i = 0;
		while (i < all->n_philo)
		{
			if (!enough_meals(all, &(meals[i]), all->philos[i]) && !alive(all, &(meals[i]), all->philos[i]))
			{
				if (waitpid(all->pids[i], &wstatus, WNOHANG) == 0)
					print_output(all, &(meals[i]), all->philos[i], DEAD);
				kill_all(all);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

static void	alone_routine(t_data *all, sem_t **cutlery, sem_t **meals, t_philo *which_philo)
{
	start_delay(all->all_start);
	sem_wait(*cutlery);
	print_output(all, meals, which_philo, FORK);
	ms_sleep(all->to_die);
	sem_post(*cutlery);
}

//TODO: FIX PICKING UP OF FORKS
static void	philosopher_routine(t_data *all, t_philo *which_philo)
{
	printf("hi I am philosopher %d\n", which_philo->index);
	sem_t *cutlery;
	sem_t *meals;
	cutlery = sem_open("cutlery", 0);
	if (which_philo->index - 1 == 0)
		meals = sem_open("meals0", 0);
	else if (which_philo->index - 1 == 1)
		meals = sem_open("meals1", 0);
	else if (which_philo->index - 1 == 2)
		meals = sem_open("meals2", 0);
	else if (which_philo->index - 1 == 3)
		meals = sem_open("meals3", 0);
	else if (which_philo->index - 1 == 4)
		meals = sem_open("meals4", 0);
	if (all->n_philo == 1)
		(alone_routine(all, &cutlery, &meals, which_philo), exit(EXIT_SUCCESS));
	start_delay(all->all_start);
	if (which_philo->index % 2)
		ms_sleep(all->to_eat);
	// if (which_philo->index % 2)
	// 	think_routine(all, which_philo, true);
	while (42)
	{
		(sem_wait(cutlery), print_output(all, &meals, which_philo, FORK));
		(sem_wait(cutlery), print_output(all, &meals, which_philo, FORK));
		// sem_wait(meals);
		which_philo->last_meal = time_ms();
		which_philo->meals++;
		// sem_post(meals);
		(print_output(all, &meals, which_philo, EAT), ms_sleep(all->to_eat));
		(sem_post(cutlery), sem_post(cutlery));
		// if (all->must_eat > 0 && which_philo->meals == all->must_eat && printf("%d: enough is enough!\n", which_philo->index))
		// 	exit(EXIT_SUCCESS);
		if (enough_meals(all, &meals, which_philo))
			exit(EXIT_SUCCESS);
		(print_output(all, &meals, which_philo, SLEEP), ms_sleep(all->to_sleep));
		//think_routine(all, which_philo, false);
	}
	exit(EXIT_FAILURE);
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
