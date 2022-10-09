/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:42:19 by ldatilio          #+#    #+#             */
/*   Updated: 2022/10/10 00:17:15 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "../philo.h"

int	is_not_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (1);
}

// int	check_eat_mutex(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->eat_mutex);
// 	if (philo->eat_count != philo->data->eat_num)
// 	{
// 		pthread_mutex_unlock(&philo->data->eat_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->data->eat_mutex);
// 	return (0);
// }

static int	eat_count_check(t_data *data)
{
	t_philo	*philo;

	philo = data->philo;
	while (1)
	{
		// pthread_mutex_lock(&data->death_mutex);
		if (philo->count_of_eat != data->number_of_eat)
		{
			// pthread_mutex_unlock(&data->death_mutex);
			return (0);
		}
		// pthread_mutex_unlock(&data->death_mutex);
		philo = philo->next;
		if (philo == data->philo)
			break ;
	}
	// data->dead = 1;
	return (1);
}

void	death_check(t_data *data)
{
	t_philo	*philo;

	usleep ((data->time_to_die * 1000) - 10);
	philo = data->philo;
	while (is_not_dead(data))
	{
		if (eat_count_check(data))
			break ;
		// pthread_mutex_lock(&data->death_mutex);
		if (get_time() - philo->last_time_eat > data->time_to_die)
		{
			printf ("%lli %i died\n", get_time() - data->start_time, philo->id);
			data->dead = 1;
		}
		// pthread_mutex_unlock(&data->death_mutex);
		philo = philo->next;
	}
}

static void	*philo_func(t_philo *philo)
{
	philo->last_time_eat = get_time();
	if (philo->data->number_of_philo == 1)
	{
		while (is_not_dead(philo->data))
			usleep(1000);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep((philo->data->time_to_eat) * 1000);
	while (is_not_dead(philo->data) \
	&& (philo->count_of_eat < philo->data->number_of_eat \
	|| philo->data->number_of_eat == -1))
	{
		philo_fork_lock(philo);
		philo_eat(philo);
		philo_fork_unlock(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	thread_init(t_data *data)
{
	t_philo	*temp;

	temp = data->philo;
	// pthread_mutex_init(&data->printer, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->start_time = get_time();
	while (1)
	{
		pthread_mutex_init(&temp->fork, NULL);
		pthread_create(&temp->thread, NULL, (void *)&philo_func, temp);
		temp = temp->next;
		if (temp == data->philo)
			break ;
	}
	death_check(data);
	while (1)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->next;
		if (temp == data->philo)
			break ;
	}
}
