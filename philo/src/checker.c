/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 04:11:23 by ldatilio          #+#    #+#             */
/*   Updated: 2022/10/16 00:13:23 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (1);
}

int	check_eat_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	if (philo->count_of_eat != philo->data->number_of_eat)
	{
		pthread_mutex_unlock(&philo->data->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_mutex);
	return (0);
}

void	death_checker(t_data *data)
{
	t_philo	*philo;

	usleep(data->time_to_die * 1000);
	philo = data->philo;
	while (check_dead(data) && check_eat_mutex(philo))
	{
		if (get_time() - philo->last_time_eat > data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->dead_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&philo->data->dead_mutex);
			pthread_mutex_lock(&philo->data->printer_mutex);
			printf("%lli %i died\n", get_time() - data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->printer_mutex);
		}
		philo = philo->next;
	}
}
