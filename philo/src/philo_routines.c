/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 01:02:53 by ldatilio          #+#    #+#             */
/*   Updated: 2022/10/14 05:05:03 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fork_lock(t_philo *philo)
{
	if (check_dead(philo->data))
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->data->printer_mutex);
		if (check_dead(philo->data))
			printf ("%lli %i has taken a fork\n",
				get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer_mutex);
		if (philo->data->number_of_philo == 1)
		{
			while (check_dead(philo->data))
				usleep(1000);
			pthread_mutex_unlock(&philo->fork);
			return ;
		}
		pthread_mutex_lock(&philo->prev->fork);
		pthread_mutex_lock(&philo->data->printer_mutex);
		if (check_dead(philo->data))
			printf ("%lli %i has taken a fork\n",
				get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer_mutex);
	}
}

void	philo_fork_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	philo_eat(t_philo *philo)
{
	if (check_dead(philo->data))
	{
		pthread_mutex_lock(&philo->data->eat_time_mutex);
		philo->last_time_eat = get_time();
		pthread_mutex_unlock(&philo->data->eat_time_mutex);
		pthread_mutex_lock(&philo->data->printer_mutex);
		if (check_dead(philo->data))
			printf ("%lli %i is eating\n",
				get_time() - philo->data->start_time, philo->id);
		pthread_mutex_lock(&philo->data->eat_mutex);
		philo->count_of_eat++;
		pthread_mutex_unlock(&philo->data->eat_mutex);
		pthread_mutex_unlock(&philo->data->printer_mutex);
		if (check_dead(philo->data))
			usleep(philo->data->time_to_eat * 1000);
	}
}

void	philo_sleep(t_philo *philo)
{
	if (check_dead(philo->data))
	{
		pthread_mutex_lock(&philo->data->printer_mutex);
		if (check_dead(philo->data))
			printf ("%lli %i is sleeping\n",
				get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer_mutex);
		if (check_dead(philo->data))
			usleep(philo->data->time_to_sleep * 1000);
	}
}

void	philo_think(t_philo *philo)
{
	if (check_dead(philo->data))
	{
		pthread_mutex_lock(&philo->data->printer_mutex);
		if (check_dead(philo->data))
			printf ("%lli %i is thinking\n",
				get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->printer_mutex);
	}
}