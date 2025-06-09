/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:45:23 by makkach           #+#    #+#             */
/*   Updated: 2025/06/09 09:00:58 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philosopher **arr)
{
	int	i;

	i = 0;
	while (arr[i])
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
	while (arr[i])
	{
		pthread_mutex_destroy(&arr[i]->mutex);
		free(arr[i]);
		i++;
	}
	free(arr);
}
