/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 11:40:55 by makkach           #+#    #+#             */
/*   Updated: 2025/05/29 18:07:31 by makkach          ###   ########.fr       */
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
		// if (tmp->left)
		// 	free(tmp->left);
		// if (tmp->right)
		// 	free(tmp->right);
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
			printf("right %d\n\n", tmp->right->fork_id);
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

void	*routine(void *param)
{
	t_philosopher	*filo = (t_philosopher *)param;
	struct timeval	current;

	gettimeofday(&current, NULL);
	filo->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
	usleep(200);
	while (1)
	{
		if (filo->state == DEAD)
			break ;
		filo->state = THINKING;
		printf("philo nbr %d is thinking\n", filo->philo_id);
		pthread_mutex_lock(&filo->left->mutex);
		// printf("-----------------philo nbr %d took fork nbr %d\n", filo->philo_id, filo->left->fork_id);
		pthread_mutex_lock(&filo->right->mutex);
		// printf("-----------------philo nbr %d took fork nbr %d\n", filo->philo_id, filo->right->fork_id);
		if (filo->state != DEAD)
			filo->state = EATING;
		else
		{
			pthread_mutex_unlock(&filo->right->mutex);
			pthread_mutex_unlock(&filo->left->mutex);
			break ;
		}
		printf("philo nbr %d is eating\n", filo->philo_id);
		usleep(filo->eating_time * 1000);
		gettimeofday(&current, NULL);
		filo->last_meal_time = current.tv_sec * 1000 + current.tv_usec / 1000;
		pthread_mutex_unlock(&filo->right->mutex);
		// printf("-----------------philo nbr %d dropped fork nbr %d\n", filo->philo_id, filo->right->fork_id);
		pthread_mutex_unlock(&filo->left->mutex);
		// printf("-----------------philo nbr %d dropped fork nbr %d\n", filo->philo_id, filo->left->fork_id);
		if (filo->state != DEAD)
			filo->state = SLEEPING;
		else
			break ;
		printf("philo nbr %d is sleeping\n", filo->philo_id);
		usleep(filo->sleep_time * 1000);
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
	long			current_time;
	int				i;
	int				how_many_philosophers;

	// atexit(f);
	if (argc != 5)
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
		head->philo_id = i;
		head->left = NULL;
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
			new_node->philo_id = i;
			new_node->left = NULL;
			new_node->state = ALIVE;
			new_node->right = NULL;
			new_node->next = NULL;
			tmp->next = new_node;
			tmp = new_node;
			i++;
		}
		i = 0;
		head_forks = malloc(sizeof(t_fork));
		head_forks->fork_id = i;
		pthread_mutex_init(&(head_forks->mutex), NULL);
		head_forks->next = NULL;
		tmp_forks = head_forks;
		i++;
		while (i < how_many_philosophers)
		{
			new_node_forks = malloc(sizeof(t_fork));
			new_node_forks->fork_id = i;
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
		// usleep(500);
		int done = 1;
		while (done)
		{
			tmp = head;
			while (tmp)
			{
				gettimeofday(&current, NULL);
				current_time = current.tv_sec * 1000 + current.tv_usec / 1000;
				if(tmp->state != EATING && current_time - tmp->last_meal_time > tmp->dying_time)
				{
					printf("current time %ld\n", current_time);
					printf("last meal time %ld\n", tmp->last_meal_time);
					printf("last dying time %d\n", tmp->dying_time);
					printf("condition %ld\n", current_time - tmp->last_meal_time );
					done = 0;
					printf("philo nbr %d is dead\n", tmp->philo_id);
					tmp2 = head;
					while (tmp2)
					{
						tmp2->state = DEAD;
						tmp2 = tmp2->next;
					}
					break ;
				}
				usleep(400);
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
