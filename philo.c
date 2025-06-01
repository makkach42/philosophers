/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 08:55:15 by makkach           #+#    #+#             */
/*   Updated: 2025/06/01 11:14:48 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	nbr;
	int		sign;
	int		n;

	i = 0;
	sign = 1;
	nbr = 0;
	n = 0;
	if (str && str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str && str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = nbr;
		nbr *= 10;
		nbr += str[i] - 48;
		if (n != nbr / 10)
			return (-1);
		i++;
	}
	return ((int)nbr * sign);
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

void	f(void)
{
	system("leaks -q philo");
}

// void *routine(void *param)
// {
// 	t_philosopher *filo = (t_philosopher *)param;
// 	struct timeval current;
// 	int counter;

// 	counter = 0;
// 	gettimeofday(&current, NULL);
// 	pthread_mutex_lock(&filo->mutexes->state_mutex);
// 	filo->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
// 	pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 	while (1)
// 	{
// 		pthread_mutex_lock(&filo->mutexes->state_mutex);
// 		if (filo->state == DEAD || (filo->times_to_eat != -1 && counter == filo->times_to_eat))
// 		{
// 			pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		if (filo->left->fork_id < filo->right->fork_id)														// LOCKING FORKS
// 		{
// 			pthread_mutex_lock(&filo->left->mutex);
// 			pthread_mutex_lock(&filo->right->mutex);
// 		}
// 		else if (filo->left->fork_id == filo->right->fork_id)
// 			break;
// 		else
// 		{
// 			pthread_mutex_lock(&filo->right->mutex);
// 			pthread_mutex_lock(&filo->left->mutex);
// 		}
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		pthread_mutex_lock(&filo->mutexes->state_mutex);													// CHECK IF DEAD AFTER WAITING FOR FORKS
// 		if (filo->state == DEAD)
// 		{
// 			pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 			if (filo->left->fork_id < filo->right->fork_id)
// 			{
// 				pthread_mutex_unlock(&filo->right->mutex);
// 				pthread_mutex_unlock(&filo->left->mutex);
// 			}
// 			else
// 			{
// 				pthread_mutex_unlock(&filo->left->mutex);
// 				pthread_mutex_unlock(&filo->right->mutex);
// 			}
// 			break;
// 		}
// 		pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 		pthread_mutex_lock(&filo->mutexes->state_mutex);
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		if (filo->mutexes->simulation_running)
// 			filo->state = EATING;																					// EATING
// 		else
// 			break ;
// 		pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 		gettimeofday(&current, NULL);
// 		pthread_mutex_lock(&filo->mutexes->state_mutex);
// 		filo->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
// 		pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 		pthread_mutex_lock(&filo->mutexes->print_mutex);
// 		gettimeofday(&current, NULL);
// 		printf("%ld %d is eating\n", 
// 			   (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, 
// 			   filo->philo_id);
// 		pthread_mutex_unlock(&filo->mutexes->print_mutex);
// 		usleep(filo->eating_time * 1000);
// 		counter++;
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		if (filo->left->fork_id < filo->right->fork_id)														//UNLOCKING FORKS
// 		{
// 			pthread_mutex_unlock(&filo->right->mutex);
// 			pthread_mutex_unlock(&filo->left->mutex);
// 		}
// 		else
// 		{
// 			pthread_mutex_unlock(&filo->left->mutex);
// 			pthread_mutex_unlock(&filo->right->mutex);
// 		}
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		pthread_mutex_lock(&filo->mutexes->state_mutex);													//SLEEPING
// 		if (filo->mutexes->simulation_running)
// 			filo->state = SLEEPING;
// 		else
// 			break ;
// 		pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 		pthread_mutex_lock(&filo->mutexes->print_mutex);
// 		gettimeofday(&current, NULL);
// 		printf("%ld %d is sleeping\n", 
// 			   (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, 
// 			   filo->philo_id);
// 		pthread_mutex_unlock(&filo->mutexes->print_mutex);
// 		usleep(filo->sleep_time * 1000);
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		pthread_mutex_lock(&filo->mutexes->state_mutex);														//THINKING
// 		if (filo->mutexes->simulation_running)
// 			filo->state = THINKING;
// 		else
// 			break ;
// 		pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 		pthread_mutex_lock(&filo->mutexes->print_mutex);
// 		gettimeofday(&current, NULL);
// 		printf("%ld %d is thinking\n", 
// 			   (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, 
// 			   filo->philo_id);
// 		pthread_mutex_unlock(&filo->mutexes->print_mutex);
// 		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 	}
	
// 	return (NULL);
// }

// void	ft_usleep(long time, t_philosopher *phil)
// {
// 	long			begining;
// 	struct timeval	current;

// 	gettimeofday(&current, NULL);
// 	begining = (current.tv_sec * 1000 + current.tv_usec / 1000);
// 	gettimeofday(&current, NULL);
// 	while ((current.tv_sec * 1000 + current.tv_usec / 1000) - begining < time)
// 	{
// 		pthread_mutex_lock(&phil->mutexes->state_mutex);
// 		if (phil->state == FINISHED || phil->state == DEAD)
// 		{
// 			pthread_mutex_unlock(&phil->mutexes->state_mutex);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&phil->mutexes->state_mutex);
// 		usleep(100);
// 	}
// }

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philosopher *philo, char *status)
{
	long	current_time;

	pthread_mutex_lock(&philo->mutexes->print_mutex);
	if (philo->mutexes->simulation_running)
	{
		current_time = get_time_ms();
		printf("%ld %d %s\n", 
			current_time - philo->mutexes->start_time, 
			philo->philo_id, 
			status);
	}
	pthread_mutex_unlock(&philo->mutexes->print_mutex);
}

void	ft_usleep(long time_ms, t_philosopher *philo)
{
	long	start_time;
	long	current_time;
	long	elapsed;

	start_time = get_time_ms();
	while (1)
	{
		pthread_mutex_lock(&philo->mutexes->state_mutex);
		if (!philo->mutexes->simulation_running || philo->state == DEAD || philo->state == FINISHED)
		{
			pthread_mutex_unlock(&philo->mutexes->state_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->mutexes->state_mutex);
		current_time = get_time_ms();
		elapsed = current_time - start_time;
		if (elapsed >= time_ms)
			break;
		usleep(100);
	}
}

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

	pthread_mutex_lock(&philo->mutexes->state_mutex);
	should_continue = philo->mutexes->simulation_running && 
					  philo->state != DEAD && 
					  philo->state != FINISHED;
	pthread_mutex_unlock(&philo->mutexes->state_mutex);
	return (should_continue);
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
			print_status(philo, "has taken a fork");
			philo->mutexes->simulation_running = 0;
			philo->state = DEAD;
			break ;
		}
		print_status(philo, "is thinking");
		take_forks(philo);
		pthread_mutex_lock(&philo->mutexes->state_mutex);
		philo->state = EATING;
		philo->last_meal_time = get_time_ms();
		pthread_mutex_unlock(&philo->mutexes->state_mutex);
		print_status(philo, "is eating");
		ft_usleep(philo->eating_time, philo);
		release_forks(philo);
		meals_eaten++;
		pthread_mutex_lock(&philo->mutexes->state_mutex);
		if (philo->times_to_eat != -1 && meals_eaten >= philo->times_to_eat)
		{
			philo->state = FINISHED;
			philo->mutexes->philos_finished++;
			if (philo->mutexes->philos_finished >= philo->mutexes->philo_count)
				philo->mutexes->simulation_running = 0;
			pthread_mutex_unlock(&philo->mutexes->state_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->mutexes->state_mutex);
		print_status(philo, "is sleeping");
		ft_usleep(philo->sleep_time, philo);
	}
	return (NULL);
}

void	arr_maker(t_philosopher ***arr, int philos_sum, char **argv)
{
	int				i;
	struct timeval	current;

	i = 0;
	(*arr) = malloc(sizeof(t_philosopher *) * (philos_sum + 1));
	while (i < philos_sum)
	{
		(*arr)[i] = malloc(sizeof(t_philosopher));
		(*arr)[i]->dying_time = ft_atoi(argv[2]);
		(*arr)[i]->eating_time = ft_atoi(argv[3]);
		(*arr)[i]->sleep_time = ft_atoi(argv[4]);
		(*arr)[i]->philo_thread = NULL;
		gettimeofday(&current, NULL);
		(*arr)[i]->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
		(*arr)[i]->philo_id = i + 1;
		(*arr)[i]->left = NULL;
		(*arr)[i]->right = NULL;
		(*arr)[i]->state = ALIVE;
		(*arr)[i]->mutexes = malloc(sizeof(t_shared_data));
		pthread_mutex_init(&(*arr)[i]->mutexes->print_mutex, NULL);
		pthread_mutex_init(&(*arr)[i]->mutexes->state_mutex, NULL);
		(*arr)[i]->mutexes->simulation_running = 1;
		(*arr)[i]->mutexes->philo_count = philos_sum;
		gettimeofday(&current, NULL);
		(*arr)[i]->mutexes->start_time = current.tv_sec * 1000 + current.tv_usec / 1000;
		if (argv[5])
			(*arr)[i]->times_to_eat = ft_atoi(argv[5]);
		else
			(*arr)[i]->times_to_eat = -1;
		(*arr)[i]->next = NULL;
		i++;
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

void	print_philos(t_philosopher **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("dying time %d\n", arr[i]->dying_time);
		printf("eating time %d\n", arr[i]->eating_time);
		printf("last meal time %ld\n", arr[i]->last_meal_time);
		printf("philo id %d\n", arr[i]->philo_id);
		printf("sleep time %d\n", arr[i]->sleep_time);
		if (arr[i]->left)
			printf("left id %d\n", arr[i]->left->fork_id);
		if (arr[i]->right)
			printf("right id %d\n\n", arr[i]->right->fork_id);
		i++;
	}
}

void	print_forks(t_fork **arr_forks)
{
	int	i;

	i = 0;
	while (arr_forks[i])
	{
		printf("fork_id = %d\n", arr_forks[i]->fork_id);
		i++;
	}
}

// void	*waiter_routine(void *param)
// {
// 	t_waiter		*waiter;
// 	struct interval	*current;
// 	int				done;
// 	int				i;

// 	waiter = (t_philosopher *)param;
// 	done = 1;
// 	i = 0;
// 	while (done)
// 	{
// 		while (waiter->arr[i])
// 		{
// 			gettimeofday(current)
// 			i++;
// 		}
// 	}
// }

int main(int argc, char *argv[])
{
	t_philosopher	**arr;
	t_fork			**arr_forks;
	// t_waiter		*waiter;
	struct timeval	current;
	long			current_time;
	int				philos_sum;
	int				i;
	int				j;
	int				done;


	if (argc != 5 && argc != 6)
		return (write(2, "parsing error\n", 15), 1);
	else
	{
		if (parsing(argv) == 1)
			return (write(2, "parsing error\n", 15), 1);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		philos_sum = ft_atoi(argv[1]);																					//INITS
		arr_maker(&arr, philos_sum, argv);
		arr[0]->mutexes->simulation_running = 1;
		fork_maker(&arr_forks, philos_sum);
		set_forks_for_philos(&arr, &arr_forks);
		print_philos(arr);
		print_forks(arr_forks);
		// waiter = malloc(sizeof(t_waiter));
		// waiter->arr = arr;
		// pthread_create(&waiter->thread, NULL, waiter_routine, (void *)waiter);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		i = 0;																										     //THREAD CREATION
		while (arr[i])
		{
			if (arr[i])
				pthread_create(&arr[i]->philo_thread, NULL, routine, (void *)arr[i]);
			i++;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		done = 1;
		while (done)																									//MONITORING
		{
			i = 0;
			j = 0;
			while (arr[i])
			{
				gettimeofday(&current, NULL);
				current_time = current.tv_sec * 1000 + current.tv_usec / 1000;
				// pthread_mutex_lock(&arr[i]->mutexes->state_mutex);
				// if (arr[j]->state == FINISHED)
				// {
				// 	j = 0;
				// 	while (arr[j])
				// 	{
				// 		pthread_detach(arr[j]->philo_thread);
				// 		// arr[i]->state = DEAD;
				// 		j++;
				// 	}
				// 	printf("done\n");
				// 	break ;
				// }
				// pthread_mutex_unlock(&arr[i]->mutexes->state_mutex);
				pthread_mutex_lock(&arr[i]->mutexes->state_mutex);
				if (arr[i]->state == DEAD || !arr[i]->mutexes->simulation_running)
				{
					if (arr[i]->state == DEAD && done)
					{
						printf("%ld %d is dead\n", get_time_ms() - arr[i]->mutexes->start_time, arr[i]->philo_id);
						done = 0;
					}
					pthread_mutex_unlock(&arr[i]->mutexes->state_mutex);
					break;
				}
				pthread_mutex_unlock(&arr[i]->mutexes->state_mutex);
				if(current_time - arr[i]->last_meal_time > arr[i]->dying_time)//arr[i]->state != EATING && arr[i]->state != FINISHED && 
				{
					printf("current time %ld\n", current_time);
					printf("last meal time %ld\n", arr[i]->last_meal_time);
					printf("last dying time %d\n", arr[i]->dying_time);
					printf("condition %ld\n", current_time - arr[i]->last_meal_time );
					done = 0;
					pthread_mutex_lock(&arr[i]->mutexes->state_mutex);
					if (arr[i]->state != FINISHED)
						printf( "%ld %d is dead\n", current_time - arr[i]->mutexes->start_time , arr[i]->philo_id);
					pthread_mutex_unlock(&arr[i]->mutexes->state_mutex);
					i = 0;
					while (arr[i])
					{
						pthread_mutex_lock(&arr[i]->mutexes->state_mutex);
						arr[i]->state = DEAD;
						arr[i]->mutexes->simulation_running = 0;
						pthread_mutex_unlock(&arr[i]->mutexes->state_mutex);
						i++;
					}
					break ;
				}
				// if (arr[i]->state == FINISHED)
				// {
				// 	j = 0;
				// 	while (arr[j])
				// 	{
				// 		if (arr[j].state)
				// 		j++;
				// 	}
				// }
				// pthread_mutex_unlock(&arr[i]->mutexes->state_mutex);
				i++;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		i = 0;																											//JOINING THREADS
		while (arr[i])
		{
			pthread_join(arr[i]->philo_thread, NULL);
			i++;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	return 0;
	}
}
