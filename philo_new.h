/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_new.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:55:36 by makkach           #+#    #+#             */
/*   Updated: 2025/06/01 09:58:14 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_NEW_H
# define PHILO_NEW_H

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
	DEAD = 4,
	FINISHED = 5
} t_state;

typedef	struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex;
	struct s_fork	*next;
}	t_fork;


typedef struct	s_shared_data
{
	int						simulation_running;
	int						philo_count;
	int						philos_finished;
	long					start_time;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			state_mutex;
	pthread_t				monitor_thread;
	struct s_philosopher	**philos;
}	t_shared_data;

typedef struct s_philosopher
{
	int				philo_id;
	pthread_t		philo_thread;
	long			last_meal_time;
	int				sleep_time;
	int				times_to_eat;
	int				eating_time;
	int				dying_time;
	t_state			state;
	t_fork			*left;
	t_fork			*right;
	t_shared_data	*mutexes;
	struct s_philosopher *next;
}	t_philosopher;


#endif