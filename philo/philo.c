/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:55:15 by makkach           #+#    #+#             */
/*   Updated: 2025/06/23 08:42:37 by makkach          ###   ########.fr       */
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
	if (monitor && (**arr)->shared_data->philo_count != 1)
	{
		result = pthread_join((*monitor), NULL);
		if (result != 0)
			return (1);
	}
	return (0);
}

static int	destroy_all(t_shared_data *shared)
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

static int	execution(t_philosopher	***arr, t_fork ***arr_forks,
			pthread_t *monitor, char **argv)
{
	int				philo_sum;
	t_shared_data	shared;
	int				results;

	philo_sum = ft_atoi(argv[1]);
	if (!philo_sum)
		return (1);
	init_shared(&shared, philo_sum);
	if (arr_maker(&(*arr), philo_sum, argv, &shared) == 1)
		return (free_philo(*arr), 1);
	(*arr)[0]->shared_data->simulation_running = 1;
	results = fork_maker(&(*arr_forks), philo_sum);
	if (results == 1 || results == 2)
		return (fork_returns(arr, arr_forks, results));
	set_forks_for_philos(&(*arr), &(*arr_forks));
	shared.philos = (*arr);
	if (create_threads(&(*arr), &(*monitor), &shared))
		return (free_philo((*arr)), free_forks((*arr_forks)), 1);
	if (join_all(&(*arr), &(*monitor)))
		return (free_philo((*arr)), free_forks((*arr_forks)),
			join_monitor(monitor), 1);
	(free_philo((*arr)), free_forks((*arr_forks)));
	if (destroy_all(&shared) != 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philosopher	**arr;
	t_fork			**arr_forks;
	pthread_t		monitor;

	if ((argc != 5 && argc != 6) || parsing(argv))
		return (write(2, "parsing error\n", 15), 1);
	else
	{
		if (execution(&arr, &arr_forks, &monitor, argv) == 1)
			return (1);
	}
}
