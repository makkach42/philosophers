/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:55:15 by makkach           #+#    #+#             */
/*   Updated: 2025/06/09 09:03:10 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks_for_philos(t_philosopher ***arr, t_fork ***arr_forks)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		(*arr)[i]->left = (*arr_forks)[i];
		if ((*arr_forks)[i + 1])
			(*arr)[i]->right = (*arr_forks)[i + 1];
		else
			(*arr)[i]->right = (*arr_forks)[0];
		i++;
	}
}

void	init_shared(t_shared_data *shared, int philo_sum)
{
	pthread_mutex_init(&shared->print_mutex, NULL);
	pthread_mutex_init(&shared->state_mutex, NULL);
	shared->simulation_running = 1;
	shared->philo_count = philo_sum;
	shared->start_time = get_time_ms();
	shared->philos_finished = 0;
}

void	create_threads(t_philosopher ***arr,
		pthread_t *monitor, t_shared_data *shared)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		if ((*arr)[i])
			pthread_create(&(*arr)[i]->philo_thread,
				NULL, routine, (void *)(*arr)[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitor_routine, shared);
}

void	join_all(t_philosopher ***arr, pthread_t *monitor)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		pthread_join((*arr)[i]->philo_thread, NULL);
		i++;
	}
	pthread_join((*monitor), NULL);
}

int	main(int argc, char *argv[])
{
	t_philosopher	**arr;
	t_fork			**arr_forks;
	pthread_t		monitor;
	int				philo_sum;
	t_shared_data	shared;

	if (argc != 5 && argc != 6)
		return (write(2, "parsing error\n", 15), 1);
	else
	{
		if (parsing(argv) == 1)
			return (write(2, "parsing error\n", 15), 1);
		philo_sum = ft_atoi(argv[1]);
		init_shared(&shared, philo_sum);
		arr_maker(&arr, philo_sum, argv, &shared);
		arr[0]->shared_data->simulation_running = 1;
		fork_maker(&arr_forks, philo_sum);
		set_forks_for_philos(&arr, &arr_forks);
		shared.philos = arr;
		create_threads(&arr, &monitor, &shared);
		join_all(&arr, &monitor);
	}
	pthread_mutex_destroy(&shared.state_mutex);
	pthread_mutex_destroy(&shared.print_mutex);
	(free_philo(arr), free_forks(arr_forks));
}
