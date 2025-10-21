/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:57:39 by mtice             #+#    #+#             */
/*   Updated: 2025/10/21 17:36:26 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//TODO: remove global variables
int	mails = 0;
pthread_mutex_t mutex;

void	init_data(t_data *all)
{
	all->philo = NULL;
	all->n_philo = 0;
	all->tdie = 0;
	all->teat = 0;
	all->tsleep = 0;
	all->must_eat = 0;
	pthread_mutex_init(&(all->mutex), NULL);
}

//TODO: remove forbidden function
void	*routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	int *value = malloc(sizeof(int));
	*value = 2;
	return ((void *)value);
}

// static int	lets_have_dinner(t_data *all)
// {
// 	// t_philo			*philo;
// 	pthread_t	th[all->n_philo];
// 	int				i;
//
// 	 // pthread_mutex_init(&(all->mutex), NULL);
// 	i = 0;
// 	while (i < all->n_philo)
// 	{
// 		if (pthread_create(th + i, NULL, &routine, NULL))
// 			return (ft_putstr_fd(THREAD, 2), 1);
// 		printf("Thread %d has started\n", i);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < all->n_philo)
// 	{
// 		if (pthread_join(th[i], NULL))
// 			return (1);
// 		printf("Thread %d has finished execution\n", i);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	// all->philo = philo;
// 	return (0);
// }

static int	lets_have_dinner(t_data *all)
{
	pthread_t	th[all->n_philo];
	int				i;
	
	i = 0;
	int	*res;
	while (i < all->n_philo)
	{
		if (pthread_create(th + i, NULL, &routine, NULL))
			return (ft_putstr_fd(THREAD, 2), 1);
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < all->n_philo)
	{
		if (pthread_join(th[i], (void **)&res))
			return (1);
		printf("Thread %d has finished execution\n", i);
		i++;
		free(res);
	}
	pthread_mutex_destroy(&mutex);
	// all->philo = philo;
	// printf("Result: %d\n", *res);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	all;
	
	init_data(&all);
	if(input_check(argc, argv) || parse_input(&all, argv)) //TODO: parse_input()
		return (1);
	lets_have_dinner(&all);
	// pthread_t p1, p2;
	// pthread_mutex_init(&mutex, NULL);
	// if (pthread_create(&p1, NULL, &routine, NULL) != 0)
	// 	return (2);
	// if (pthread_create(&p2, NULL, &routine, NULL) != 0)
	// 	return (3);
	// if (pthread_join(p1, NULL) != 0)
	// 	return (4);
	// if (pthread_join(p2, NULL) != 0)
	// 	return (5);
	// pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	printf("Number of philosophers: %-20d\n", all.n_philo);
	printf("Time to die: %-20d\n", all.tdie);
	printf("Time to eat: %-20d\n", all.teat);
	printf("Time to sleep: %-20d\n", all.tsleep);
	printf("Each must eat: %-20d\n", all.must_eat);
	return (0);
}
