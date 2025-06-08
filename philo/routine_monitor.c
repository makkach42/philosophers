/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:01:38 by makkach           #+#    #+#             */
/*   Updated: 2025/06/06 15:00:10 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_philosopher_death(t_shared_data *shared, t_philosopher *philo,
		long current_time)
{
	shared->simulation_running = 0;
	philo->state = DEAD;
	pthread_mutex_unlock(&shared->state_mutex);
	pthread_mutex_lock(&shared->print_mutex);
	printf("%ld %d died\n", current_time - shared->start_time,
		philo->philo_id);
	pthread_mutex_unlock(&shared->print_mutex);
}

int	check_single_philosopher_death(t_shared_data *shared, int index)
{
	t_philosopher	*philo;
	long			current_time;
	int				is_dead;

	philo = shared->philos[index];
	pthread_mutex_lock(&shared->state_mutex);
	current_time = get_time_ms();
	is_dead = (philo->state != FINISHED && philo->state != DEAD
			&& current_time - philo->last_meal_time > philo->dying_time);
	if (is_dead)
	{
		handle_philosopher_death(shared, philo, current_time);
		pthread_mutex_unlock(&shared->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&shared->state_mutex);
	return (0);
}

int	check_philosophers_death(t_shared_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->philo_count)
	{
		if (check_single_philosopher_death(shared, i))
			return (1);
		i++;
	}
	return (0);
}

int	check_simulation_running(t_shared_data *shared)
{
	int	running;

	pthread_mutex_lock(&shared->state_mutex);
	running = shared->simulation_running;
	pthread_mutex_unlock(&shared->state_mutex);
	return (running);
}

void	*monitor_routine(void *arg)
{
	t_shared_data	*shared;

	shared = (t_shared_data *)arg;
	while (1)
	{
		usleep(1000);
		if (!check_simulation_running(shared))
			break ;
		if (check_philosophers_death(shared))
			return (NULL);
	}
	return (NULL);
}
