/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:42:19 by ldatilio          #+#    #+#             */
/*   Updated: 2022/10/10 07:46:54 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "../philo.h"

void	death_check(t_data *data)
{
	t_philo	*philo;

	usleep(data->time_to_die * 1000);
	philo = data->philo;
	while (data->dead == 0 && (philo->count_of_eat != data->number_of_eat))
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (get_time() - philo->last_time_eat > data->time_to_die)
		{
			data->dead = 1;
			printf ("%lli %i died\n", get_time() - data->start_time, philo->id);
		}
		philo = philo->next;
		pthread_mutex_unlock(&philo->data->mutex);
	}
}

static void	*philo_func(t_philo *philo)
{
	philo->last_time_eat = get_time();
	if (philo->data->number_of_philo == 1)
	{
		while (philo->data->dead == 0)
			usleep(1000);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (philo->data->dead == 0 \
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
	pthread_mutex_init(&data->mutex, NULL);
	data->start_time = get_time();
	while (1)
	{
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
