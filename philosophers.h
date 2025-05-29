/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:41:36 by makkach           #+#    #+#             */
/*   Updated: 2025/05/29 17:45:16 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef enum state
{
	ALIVE = 0,
	THINKING = 1,
	SLEEPING = 2,
	EATING = 3,
	DEAD = 4
} t_state;

typedef	struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex;
	struct s_fork	*next;
}	t_fork;

typedef struct s_philosopher
{
	int				philo_id;
	pthread_t		philo_thread;
	long			last_meal_time;
	int				sleep_time;
	int				eating_time;
	int				dying_time;
	t_state			state;
	t_fork			*left;
	t_fork			*right;
	struct s_philosopher *next;
}	t_philosopher;

#endif