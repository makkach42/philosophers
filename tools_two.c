/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:52:07 by makkach           #+#    #+#             */
/*   Updated: 2025/06/06 12:02:38 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->left->fork_id < philo->right->fork_id)
	{
		pthread_mutex_lock(&philo->left->mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right->mutex);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right->mutex);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left->mutex);
		print_status(philo, "has taken a fork");
	}
}

void	release_forks(t_philosopher *philo)
{
	if (philo->left->fork_id < philo->right->fork_id)
	{
		pthread_mutex_unlock(&philo->right->mutex);
		pthread_mutex_unlock(&philo->left->mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->left->mutex);
		pthread_mutex_unlock(&philo->right->mutex);
	}
}

int	check_simulation_state(t_philosopher *philo)
{
	int	should_continue;

	pthread_mutex_lock(&philo->shared_data->state_mutex);
	should_continue = (philo->shared_data->simulation_running
			) && (philo->state
			) != DEAD && (philo->state) != FINISHED;
	pthread_mutex_unlock(&philo->shared_data->state_mutex);
	return (should_continue);
}

void	arr_maker(t_philosopher ***arr,
		int philos_sum, char **argv, t_shared_data *shared)
{
	int				i;
	struct timeval	current;

	i = -1;
	(*arr) = malloc(sizeof(t_philosopher *) * (philos_sum + 1));
	while (++i < philos_sum)
	{
		(*arr)[i] = malloc(sizeof(t_philosopher));
		(*arr)[i]->dying_time = ft_atoi(argv[2]);
		(*arr)[i]->eating_time = ft_atoi(argv[3]);
		(*arr)[i]->sleep_time = ft_atoi(argv[4]);
		(*arr)[i]->philo_thread = NULL;
		(*arr)[i]->last_meal_time = shared->start_time;
		(*arr)[i]->philo_id = i + 1;
		(*arr)[i]->left = NULL;
		(*arr)[i]->right = NULL;
		(*arr)[i]->state = ALIVE;
		(*arr)[i]->shared_data = shared;
		if (argv[5])
			(*arr)[i]->times_to_eat = ft_atoi(argv[5]);
		else
			(*arr)[i]->times_to_eat = -1;
	}
	(*arr)[i] = NULL;
}

void	fork_maker(t_fork ***arr_forks, int philos_sum)
{
	int	i;

	(*arr_forks) = malloc(sizeof(t_fork *) * (philos_sum + 1));
	i = 0;
	while (i < philos_sum)
	{
		(*arr_forks)[i] = malloc(sizeof(t_fork));
		(*arr_forks)[i]->fork_id = i + 1;
		pthread_mutex_init(&(*arr_forks)[i]->mutex, NULL);
		i++;
	}
	(*arr_forks)[i] = NULL;
}
