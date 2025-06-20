/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:45:23 by makkach           #+#    #+#             */
/*   Updated: 2025/06/20 16:16:32 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philosopher **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_forks(t_fork **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		pthread_mutex_destroy(&arr[i]->mutex);
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_forks_to_idx(t_fork **arr, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		if (i < j)
			pthread_mutex_destroy(&arr[i]->mutex);
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	fork_returns(t_philosopher ***arr, t_fork ***arr_forks, int results)
{
	if (results == 1)
		return (free_philo((*arr)), free_forks(*arr_forks), 1);
	else if (results == 2)
		return (free_philo((*arr)), 1);
	return (0);
}
