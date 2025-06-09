/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:55:36 by makkach           #+#    #+#             */
/*   Updated: 2025/06/09 09:00:17 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum state
{
	ALIVE = 0,
	THINKING = 1,
	SLEEPING = 2,
	EATING = 3,
	DEAD = 4,
	FINISHED = 5
}	t_state;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_shared_data
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
	int						philo_id;
	pthread_t				philo_thread;
	long					last_meal_time;
	int						sleep_time;
	int						times_to_eat;
	int						eating_time;
	int						dying_time;
	t_state					state;
	t_fork					*left;
	t_fork					*right;
	t_shared_data			*shared_data;
}	t_philosopher;

void	ft_usleep(long time_ms, t_philosopher *philo);
void	print_status(t_philosopher *philo, char *status);
long	get_time_ms(void);
int		parsing(char **argv);
int		ft_atoi(char *str);
void	fork_maker(t_fork ***arr_forks, int philos_sum);
void	arr_maker(t_philosopher ***arr,
			int philos_sum, char **argv, t_shared_data *shared);
int		check_simulation_state(t_philosopher *philo);
void	release_forks(t_philosopher *philo);
void	take_forks(t_philosopher *philo);
void	*routine(void *arg);
void	*monitor_routine(void *arg);
void	free_philo(t_philosopher **arr);
void	free_forks(t_fork **arr);

#endif
