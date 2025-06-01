/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:55 by makkach           #+#    #+#             */
/*   Updated: 2025/05/31 13:19:42 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
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

void	free_philos(t_philosopher *head)
{
	t_philosopher	*tmp;
	t_philosopher	*tmp2;

	tmp = head;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->mutexes);
		free(tmp);
		tmp = tmp2;
	}
}

void	free_forks(t_fork *head)
{
	t_fork	*tmp;
	t_fork	*tmp2;

	tmp = head;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void	f(void)
{
	system("leaks -q philo");
}

void	print_philos_lnkdlst(t_philosopher *head)
{
	t_philosopher	*tmp;
	tmp = head;
	while (tmp)
	{
		printf("dying time %d\n", tmp->dying_time);
		printf("eating time %d\n", tmp->eating_time);
		printf("last meal time %ld\n", tmp->last_meal_time);
		printf("philo id %d\n", tmp->philo_id);
		printf("sleep time %d\n", tmp->sleep_time);
		if (tmp->left)
			printf("left id %d\n", tmp->left->fork_id);
		if (tmp->right)
			printf("right id %d\n\n", tmp->right->fork_id);
		tmp = tmp->next;
	}
}

void	print_forks(t_fork *head)
{
	t_fork	*tmp_forks;

	tmp_forks = head;
	while (tmp_forks)
	{
		printf("fork_id = %d\n", tmp_forks->fork_id);
		tmp_forks = tmp_forks->next;
	}
}

// void	ft_usleep(long long time, t_philosopher *filo)
// {
// 	int				i;
// 	long			current_time;
// 	struct timeval	current;
	
// 	i = 100;
// 	while (i < time)
// 	{
// 		gettimeofday(&current, NULL);
// 		current_time = current.tv_sec * 1000 + current.tv_usec / 1000;
// 		if (filo->state != EATING && current_time - filo->last_meal_time > filo->dying_time)
// 		{
// 			filo->state = DEAD;
// 			break ;
// 		}
// 		usleep(i);
// 		i += i;
// 	}
// }

// void ft_usleep(long long time_ms, t_philosopher *filo)
// {
//     struct timeval start, current;
//     long elapsed_ms;
// 	pthread_mutex_t	g_state_mutex;
	
//     gettimeofday(&start, NULL);
// 	pthread_mutex_init(&g_state_mutex, NULL);
//     while (1)
//     {
//         pthread_mutex_lock(&g_state_mutex);
//         if (filo->state == DEAD)
//         {
//             pthread_mutex_unlock(&g_state_mutex);
//             break;
//         }
//         pthread_mutex_unlock(&g_state_mutex);
//         gettimeofday(&current, NULL);
//         elapsed_ms = (current.tv_sec - start.tv_sec) * 1000 + 
//                     (current.tv_usec - start.tv_usec) / 1000;
//         if (elapsed_ms >= time_ms)
//             break;
//         usleep(1000);
//     }
// }

void ft_usleep(long long time_ms, t_philosopher *filo)
{
	struct timeval start, current;
	long elapsed_ms;
	
	gettimeofday(&start, NULL);
	while (1)
	{
		pthread_mutex_lock(&filo->mutexes->state_mutex);
		if (filo->state == DEAD)
		{
			pthread_mutex_unlock(&filo->mutexes->state_mutex);
			break;
		}
		pthread_mutex_unlock(&filo->mutexes->state_mutex);
		gettimeofday(&current, NULL);
		elapsed_ms = (current.tv_sec - start.tv_sec) * 1000 + 
					(current.tv_usec - start.tv_usec) / 1000;
		if (elapsed_ms >= time_ms / 1000)
			break ;
		usleep(1000);
	}
}

// void	*routine(void *param)
// {
// 	t_philosopher	*filo = (t_philosopher *)param;
// 	struct timeval	current;
// 	int				counter;

// 	gettimeofday(&current, NULL);
// 	pthread_mutex_init(&filo->mutexes->state_mutex, NULL);
// 	counter = 0;
// 	pthread_mutex_lock(&filo->mutexes->state_mutex);
// 	filo->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
// 	pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 	while (1)
// 	{
// 		if (filo->state == DEAD)
// 			break ;
// 		pthread_mutex_lock(&filo->mutexes->state_mutex);
// 		if (filo->times_to_eat != -1 && counter == filo->times_to_eat)
// 		{
// 			pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 		// pthread_mutex_lock(&state_mutex);
// 		// filo->state = THINKING;
// 		// pthread_mutex_unlock(&state_mutex);
// 		// gettimeofday(&current, NULL);
// 		// printf("%ld %d is thinking\n", (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, filo->philo_id);
// 		if (filo->left->fork_id < filo->right->fork_id)
// 		{
// 			pthread_mutex_lock(&filo->left->mutex);
// 			// printf("----------------%d has taken the fork %d in his left\n", filo->philo_id, filo->left->fork_id);
// 			pthread_mutex_lock(&filo->right->mutex);
// 			// printf("----------------%d has taken the fork %d in his right\n", filo->philo_id, filo->right->fork_id);
// 		}
// 		else if (filo->left->fork_id == filo->right->fork_id)
// 			break ;
// 		else
// 		{
// 			pthread_mutex_lock(&filo->right->mutex);
// 			// printf("----------------%d has taken the fork %d in his right\n", filo->philo_id, filo->right->fork_id);
// 			pthread_mutex_lock(&filo->left->mutex);
// 			// // printf("----------------%d has taken the fork %d in his left\n", filo->philo_id, filo->left->fork_id);
// 		}
//         pthread_mutex_lock(&filo->mutexes->state_mutex);
//         if (filo->state == DEAD)
//         {
//             pthread_mutex_unlock(&filo->mutexes->state_mutex);
//             if (filo->left->fork_id < filo->right->fork_id)
//             {
//                 pthread_mutex_unlock(&filo->right->mutex);
//                 pthread_mutex_unlock(&filo->left->mutex);
//             }
//             else
//             {
//                 pthread_mutex_unlock(&filo->left->mutex);
//                 pthread_mutex_unlock(&filo->right->mutex);
//             }
//             break;
//         }
// 		if (filo->state != DEAD)
// 		{
// 			pthread_mutex_lock(&filo->mutexes->state_mutex);
// 			filo->state = EATING;
// 			pthread_mutex_unlock(&filo->mutexes->state_mutex);;
// 		}
// 		if (filo->state != DEAD)
// 		{
// 			pthread_mutex_lock(&filo->mutexes->print_mutex);
// 			gettimeofday(&current, NULL);
// 			printf("%ld %d is eating\n", (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, filo->philo_id);
// 			pthread_mutex_unlock(&filo->mutexes->print_mutex);
// 			ft_usleep(filo->eating_time * 1000, filo);
// 			counter++;
// 			gettimeofday(&current, NULL);
// 			filo->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
// 		}
// 		if (filo->left->fork_id < filo->right->fork_id)
// 		{
// 			pthread_mutex_unlock(&filo->right->mutex);
// 			// printf("++++++++++++++++%d has put down the fork %d in his right\n", filo->philo_id, filo->right->fork_id);
// 			pthread_mutex_unlock(&filo->left->mutex);
// 			// printf("++++++++++++++++%d has put down the fork %d in his left\n", filo->philo_id, filo->left->fork_id);
// 		}
// 		else
// 		{
// 			pthread_mutex_unlock(&filo->left->mutex);
// 			// printf("++++++++++++++++%d has put down the fork %d in his left\n", filo->philo_id, filo->left->fork_id);
// 			pthread_mutex_unlock(&filo->right->mutex);
// 			// printf("++++++++++++++++%d has put down the fork %d in his right\n", filo->philo_id, filo->right->fork_id);
// 		}
// 		if (filo->state != DEAD)
// 		{
// 			pthread_mutex_lock(&filo->mutexes->state_mutex);
// 			filo->state = SLEEPING;
// 			pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 		}
// 		gettimeofday(&current, NULL);
// 		if (filo->state != DEAD)
// 		{
// 			pthread_mutex_lock(&filo->mutexes->print_mutex);
// 			printf("%ld %d is sleeping\n", (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, filo->philo_id);
// 			pthread_mutex_unlock(&filo->mutexes->print_mutex);
// 		}
// 		ft_usleep(filo->sleep_time * 1000, filo);
// 		if (filo->state != DEAD)
// 		{
// 			pthread_mutex_lock(&filo->mutexes->state_mutex);
// 			filo->state = THINKING;
// 			pthread_mutex_unlock(&filo->mutexes->state_mutex);
// 		}
// 		gettimeofday(&current, NULL);
// 		if (filo->state != DEAD)
// 		{
// 			pthread_mutex_lock(&filo->mutexes->print_mutex);
// 			printf("%ld %d is thinking\n", (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, filo->philo_id);
// 			pthread_mutex_unlock(&filo->mutexes->print_mutex);
// 		}

// 	}
// 	return (NULL);
// }

void *routine(void *param)
{
	t_philosopher *filo = (t_philosopher *)param;
	struct timeval current;
	int counter;

	counter = 0;
	gettimeofday(&current, NULL);
	pthread_mutex_lock(&filo->mutexes->state_mutex);
	filo->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
	pthread_mutex_unlock(&filo->mutexes->state_mutex);
	while (1)
	{
		pthread_mutex_lock(&filo->mutexes->state_mutex);
		if (filo->state == DEAD || (filo->times_to_eat != -1 && counter == filo->times_to_eat))
		{
			pthread_mutex_unlock(&filo->mutexes->state_mutex);
			break;
		}
		pthread_mutex_unlock(&filo->mutexes->state_mutex);
		if (filo->left->fork_id < filo->right->fork_id)
		{
			pthread_mutex_lock(&filo->left->mutex);
			pthread_mutex_lock(&filo->right->mutex);
		}
		else if (filo->left->fork_id == filo->right->fork_id)
			break;
		else
		{
			pthread_mutex_lock(&filo->right->mutex);
			pthread_mutex_lock(&filo->left->mutex);
		}
		pthread_mutex_lock(&filo->mutexes->state_mutex);
		if (filo->state == DEAD)
		{
			pthread_mutex_unlock(&filo->mutexes->state_mutex);
			if (filo->left->fork_id < filo->right->fork_id)
			{
				pthread_mutex_unlock(&filo->right->mutex);
				pthread_mutex_unlock(&filo->left->mutex);
			}
			else
			{
				pthread_mutex_unlock(&filo->left->mutex);
				pthread_mutex_unlock(&filo->right->mutex);
			}
			break;
		}
		pthread_mutex_unlock(&filo->mutexes->state_mutex);
		pthread_mutex_lock(&filo->mutexes->state_mutex);
		filo->state = EATING;
		pthread_mutex_unlock(&filo->mutexes->state_mutex);
		gettimeofday(&current, NULL);
		pthread_mutex_lock(&filo->mutexes->state_mutex);
		filo->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
		pthread_mutex_unlock(&filo->mutexes->state_mutex);
		pthread_mutex_lock(&filo->mutexes->print_mutex);
		gettimeofday(&current, NULL);
		printf("%ld %d is eating\n", 
			   (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, 
			   filo->philo_id);
		pthread_mutex_unlock(&filo->mutexes->print_mutex);
		ft_usleep(filo->eating_time * 1000, filo);
		counter++;
		if (filo->left->fork_id < filo->right->fork_id)
		{
			pthread_mutex_unlock(&filo->right->mutex);
			pthread_mutex_unlock(&filo->left->mutex);
		}
		else
		{
			pthread_mutex_unlock(&filo->left->mutex);
			pthread_mutex_unlock(&filo->right->mutex);
		}
		pthread_mutex_lock(&filo->mutexes->state_mutex);
		if (filo->state != DEAD)
			filo->state = SLEEPING;
		pthread_mutex_unlock(&filo->mutexes->state_mutex);
		pthread_mutex_lock(&filo->mutexes->print_mutex);
		gettimeofday(&current, NULL);
		printf("%ld %d is sleeping\n", 
			   (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, 
			   filo->philo_id);
		pthread_mutex_unlock(&filo->mutexes->print_mutex);
		ft_usleep(filo->sleep_time * 1000, filo);
		pthread_mutex_lock(&filo->mutexes->state_mutex);
		if (filo->state != DEAD)
			filo->state = THINKING;
		pthread_mutex_unlock(&filo->mutexes->state_mutex);
		pthread_mutex_lock(&filo->mutexes->print_mutex);
		gettimeofday(&current, NULL);
		printf("%ld %d is thinking\n", 
			   (current.tv_sec * 1000 + current.tv_usec / 1000) - filo->time_simulation_started, 
			   filo->philo_id);
		pthread_mutex_unlock(&filo->mutexes->print_mutex);
	}
	
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philosopher	*head;
	t_philosopher	*new_node;
	t_philosopher	*tmp;
	t_philosopher	*tmp2;
	t_fork			*head_forks;
	t_fork			*new_node_forks;
	t_fork			*tmp_forks;
	struct timeval	current;
	pthread_mutex_t	state_mutex;
	long			current_time;
	int				i;
	int				how_many_philosophers;

	if (argc != 5 && argc != 6)
		return (write(2, "parsing error\n", 15), 1);
	else
	{
		if (parsing(argv) == 1)
			return (write(2, "parsing error\n", 15), 1);
		i = 0;
		how_many_philosophers = ft_atoi(argv[1]);
		head = malloc(sizeof(t_philosopher));
		head->dying_time = ft_atoi(argv[2]);
		head->eating_time = ft_atoi(argv[3]);
		head->sleep_time = ft_atoi(argv[4]);
		gettimeofday(&current, NULL);
		head->time_simulation_started = current.tv_sec * 1000 + current.tv_usec / 1000;
		head->mutexes = malloc(sizeof(t_data));
		pthread_mutex_init(&head->mutexes->state_mutex, NULL);
		pthread_mutex_init(&head->mutexes->print_mutex, NULL);
		gettimeofday(&current, NULL);
		head->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
		head->philo_id = i + 1;
		head->left = NULL;
		if (argv[5])
			head->times_to_eat = ft_atoi(argv[5]);
		else
			head->times_to_eat = -1;
		head->state = ALIVE;
		head->right = NULL;
		head->next = NULL;
		tmp = head;
		i++;
		while (i < how_many_philosophers)
		{
			new_node = malloc(sizeof(t_philosopher));
			new_node->dying_time = ft_atoi(argv[2]);
			new_node->eating_time = ft_atoi(argv[3]);
			new_node->sleep_time = ft_atoi(argv[4]);
			new_node->time_simulation_started = head->time_simulation_started;
			gettimeofday(&current, NULL);
			new_node->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
			new_node->philo_id = i + 1;
			new_node->mutexes = malloc(sizeof(t_data));
			pthread_mutex_init(&new_node->mutexes->print_mutex, NULL);
			pthread_mutex_init(&new_node->mutexes->state_mutex, NULL);
			new_node->left = NULL;
			if (argv[5])
				new_node->times_to_eat = ft_atoi(argv[5]);
			else
				new_node->times_to_eat = -1;
			new_node->state = ALIVE;
			new_node->right = NULL;
			new_node->next = NULL;
			tmp->next = new_node;
			tmp = new_node;
			i++;
		}
		i = 0;
		head_forks = malloc(sizeof(t_fork));
		head_forks->fork_id = i + 1;
		pthread_mutex_init(&(head_forks->mutex), NULL);
		head_forks->next = NULL;
		tmp_forks = head_forks;
		i++;
		while (i < how_many_philosophers)
		{
			new_node_forks = malloc(sizeof(t_fork));
			new_node_forks->fork_id = i + 1;
			pthread_mutex_init(&(new_node_forks->mutex), NULL);
			new_node_forks->next = NULL;
			tmp_forks->next = new_node_forks;
			tmp_forks = new_node_forks;
			i++;
		}
		tmp = head;
		tmp_forks = head_forks;
		while (tmp)
		{
			tmp->left = tmp_forks;
			if (tmp_forks->next)
				tmp->right = tmp_forks->next;
			else
				tmp->right = head_forks;
			tmp = tmp->next;
			tmp_forks = tmp_forks->next;
		}
		print_philos_lnkdlst(head);
		printf("\n");
		print_forks(head_forks);
		printf("\n");
		tmp = head;
		while (tmp)
		{
			pthread_create(&tmp->philo_thread, NULL, routine, (void *)tmp);
			tmp = tmp->next;
		}
		int done = 1;
		pthread_mutex_init(&state_mutex, NULL);
		while (done)
		{
			
			tmp = head;
			while (tmp)
			{
				gettimeofday(&current, NULL);
				current_time = current.tv_sec * 1000 + current.tv_usec / 1000;
				pthread_mutex_lock(&tmp->mutexes->state_mutex);
				if(current_time - tmp->last_meal_time > tmp->dying_time)//tmp->state != EATING && 
				{
					printf("current time %ld\n", current_time);
					printf("last meal time %ld\n", tmp->last_meal_time);
					printf("last dying time %d\n", tmp->dying_time);
					printf("condition %ld\n", current_time - tmp->last_meal_time );
					done = 0;
					printf( "%ld %d is dead\n", current_time - tmp->time_simulation_started , tmp->philo_id);
					pthread_mutex_unlock(&tmp->mutexes->state_mutex);
					tmp2 = head;
					while (tmp2)
					{
						pthread_mutex_lock(&tmp2->mutexes->state_mutex);
						tmp2->state = DEAD;
						pthread_mutex_unlock(&tmp2->mutexes->state_mutex);
						tmp2 = tmp2->next;
					}
					break ;
				}
				pthread_mutex_unlock(&tmp->mutexes->state_mutex);
				tmp = tmp->next;
			}
		}
		tmp = head;
		while (tmp)
		{
			pthread_join(tmp->philo_thread, NULL);
			tmp = tmp->next;
		}
	}
	free_philos(head);
	free_forks(head_forks);
}
