/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:49:42 by makkach           #+#    #+#             */
/*   Updated: 2025/06/23 08:34:11 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	int		nbr;
	int		sign;
	int		n;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str && str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = nbr;
		nbr = nbr * 10 + (str[i] - 48);
		if (nbr / 10 != n)
			return (-1);
		i++;
	}
	return (nbr * sign);
}

int	parsing(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

long	get_current_time_ms(void)
{
	struct timeval	time;
	long			time_ms;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_ms);
}

void	print_status(t_philosopher *philo, char *status)
{
	long	current_time;

	pthread_mutex_lock(&philo->shared_data->state_mutex);
	if (philo->shared_data->simulation_running)
	{
		current_time = get_current_time_ms();
		pthread_mutex_lock(&philo->shared_data->print_mutex);
		printf("%ld %d %s\n",
			current_time - philo->shared_data->start_time,
			philo->philo_id,
			status);
		pthread_mutex_unlock(&philo->shared_data->print_mutex);
	}
	pthread_mutex_unlock(&philo->shared_data->state_mutex);
}

void	ft_usleep(long time_ms, t_philosopher *philo)
{
	long	start_time;
	long	current_time;
	long	elapsed;

	start_time = get_current_time_ms();
	while (1)
	{
		pthread_mutex_lock(&philo->shared_data->state_mutex);
		if ((!philo->shared_data->simulation_running
			) || (philo->state == DEAD
			) || (philo->state == FINISHED))
		{
			pthread_mutex_unlock(&philo->shared_data->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->shared_data->state_mutex);
		current_time = get_current_time_ms();
		elapsed = current_time - start_time;
		if (elapsed >= time_ms)
			break ;
		usleep(100);
	}
}
