/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:55:15 by makkach           #+#    #+#             */
/*   Updated: 2025/06/09 09:54:11 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_all(t_philosopher ***arr, pthread_t *monitor)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((*arr)[i])
	{
		result = pthread_join((*arr)[i]->philo_thread, NULL);
		if (result != 0)
			return (1);
		i++;
	}
	result = pthread_join((*monitor), NULL);
	if (result != 0)
		return (1);
	return (0);
}

int	destroy_all(t_shared_data *shared)
{
	int	result;

	result = 0;
	result = pthread_mutex_destroy(&(*shared).state_mutex);
	if (result != 0)
		return (1);
	result = pthread_mutex_destroy(&(*shared).print_mutex);
	if (result != 0)
		return (1);
	return (0);
}

int	execution(t_philosopher	***arr, t_fork ***arr_forks,
	pthread_t *monitor, char **argv)
{
	int				philo_sum;
	t_shared_data	shared;

	philo_sum = 0;
	if (parsing(argv) == 1)
		return (write(2, "parsing error\n", 15), 1);
	philo_sum = ft_atoi(argv[1]);
	init_shared(&shared, philo_sum);
	if (arr_maker(&(*arr), philo_sum, argv, &shared) == 1)
		return (1);
	(*arr)[0]->shared_data->simulation_running = 1;
	if (fork_maker(&(*arr_forks), philo_sum) == 1)
		return (free_philo((*arr)), 1);
	set_forks_for_philos(&(*arr), &(*arr_forks));
	shared.philos = (*arr);
	if (create_threads(&(*arr), &(*monitor), &shared))
		return (free_philo((*arr)), free_forks((*arr_forks)), 1);
	if (join_all(&(*arr), &(*monitor)))
		return (free_philo((*arr)), free_forks((*arr_forks)), 1);
	(free_philo((*arr)), free_forks((*arr_forks)));
	if (destroy_all(&shared) != 0)
		return (1);
	return (0);
}

void	f(void)
{
	system("leaks -q philo");
}

int	main(int argc, char *argv[])
{
	t_philosopher	**arr;
	t_fork			**arr_forks;
	pthread_t		monitor;

	atexit(f);
	if (argc != 5 && argc != 6)
		return (write(2, "parsing error\n", 15), 1);
	else
	{
		if (execution(&arr, &arr_forks, &monitor, argv) == 1)
			return (1);
	}
}
