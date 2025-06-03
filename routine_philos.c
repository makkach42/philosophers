/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:26:23 by makkach           #+#    #+#             */
/*   Updated: 2025/06/03 14:27:48 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_case(t_philosopher **philo)
{
	print_status((*philo), "has taken a fork");
	print_status((*philo), "is dead");
	(*philo)->mutexes->simulation_running = 0;
}

void	if_finished(t_philosopher **philo)
{
	(*philo)->state = FINISHED;
	(*philo)->mutexes->philos_finished++;
	if ((*philo)->mutexes->philos_finished >= (*philo)->mutexes->philo_count)
		(*philo)->mutexes->simulation_running = 0;
	pthread_mutex_unlock(&(*philo)->mutexes->state_mutex);
}

void	eating_logic(int *meals_eaten, t_philosopher **philo)
{
	take_forks((*philo));
	pthread_mutex_lock(&(*philo)->mutexes->state_mutex);
	(*philo)->state = EATING;
	(*philo)->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&(*philo)->mutexes->state_mutex);
	print_status((*philo), "is eating");
	ft_usleep((*philo)->eating_time, (*philo));
	release_forks((*philo));
	(*meals_eaten)++;
}

void	sleeping_logic(t_philosopher **philo)
{
	print_status((*philo), "is sleeping");
	ft_usleep((*philo)->sleep_time, (*philo));
	print_status((*philo), "is thinking");
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	int				meals_eaten;

	philo = (t_philosopher *)arg;
	meals_eaten = 0;
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->eating_time / 2, philo);
	while (check_simulation_state(philo))
	{
		if (philo->mutexes->philo_count == 1)
		{
			one_philo_case(&philo);
			break ;
		}
		eating_logic(&meals_eaten, &philo);
		pthread_mutex_lock(&philo->mutexes->state_mutex);
		if (philo->times_to_eat != -1 && meals_eaten >= philo->times_to_eat)
		{
			if_finished(&philo);
			break ;
		}
		pthread_mutex_unlock(&philo->mutexes->state_mutex);
		sleeping_logic(&philo);
	}
	return (NULL);
}
