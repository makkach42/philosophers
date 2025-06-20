/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:53:33 by makkach           #+#    #+#             */
/*   Updated: 2025/06/20 08:46:19 by makkach          ###   ########.fr       */
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

int	create_threads(t_philosopher ***arr,
		pthread_t *monitor, t_shared_data *shared)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((*arr)[i])
	{
		if ((*arr)[i])
		{
			result = pthread_create(&(*arr)[i]->philo_thread,
					NULL, routine, (void *)(*arr)[i]);
			if (result != 0)
				return (join_all(arr, NULL), 1);
		}
		i++;
	}
	if (shared->philo_count != 1)
	{
		result = pthread_create(monitor, NULL, monitor_routine, shared);
		if (result != 0)
			return (1);
	}
	return (0);
}

void	arr_maker_helper(t_philosopher ***arr, char **argv, int i)
{
	(*arr)[i]->dying_time = ft_atoi(argv[2]);
	(*arr)[i]->eating_time = ft_atoi(argv[3]);
	(*arr)[i]->sleep_time = ft_atoi(argv[4]);
}
