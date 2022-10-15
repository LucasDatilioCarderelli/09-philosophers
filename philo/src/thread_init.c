/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:42:19 by ldatilio          #+#    #+#             */
/*   Updated: 2022/10/16 00:13:15 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_func(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_time_mutex);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->data->eat_time_mutex);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (check_dead(philo->data) \
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
	data->start_time = get_time();
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->printer_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->eat_time_mutex, NULL);
	while (1)
	{
		pthread_create(&temp->thread, NULL, (void *)&philo_func, temp);
		temp = temp->next;
		if (temp == data->philo)
			break ;
	}
	death_checker(data);
	while (1)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->next;
		if (temp == data->philo)
			break ;
	}
}
