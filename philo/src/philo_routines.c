/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 01:02:53 by ldatilio          #+#    #+#             */
/*   Updated: 2022/10/10 00:23:41 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fork_lock(t_philo *philo)
{
	if (is_not_dead(philo->data))
	{
		pthread_mutex_lock(&philo->fork);
		// pthread_mutex_lock(&philo->data->printer);
		if (is_not_dead(philo->data))
			printf("%lli %i has taken a fork\n",
				get_time() - philo->data->start_time, philo->id);
		// pthread_mutex_unlock(&philo->data->printer);
		pthread_mutex_lock(&philo->prev->fork);
		// pthread_mutex_lock(&philo->data->printer);
		if (is_not_dead(philo->data))
			printf("%lli %i has taken a fork\n",
				get_time() - philo->data->start_time, philo->id);
		// pthread_mutex_unlock(&philo->data->printer);
	}
}

void	philo_fork_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	philo_eat(t_philo *philo)
{
	if (is_not_dead(philo->data))
	{
		philo->last_time_eat = get_time();
		// pthread_mutex_lock(&philo->data->printer);
		// if (is_not_dead(philo->data))
			printf("%lli %i is eating\n",
				get_time() - philo->data->start_time, philo->id);
		philo->count_of_eat++;
		// pthread_mutex_unlock(&philo->data->printer);
		usleep(philo->data->time_to_eat * 1000);
	}
}

void	philo_sleep(t_philo *philo)
{
	if (is_not_dead(philo->data))
	{
		// pthread_mutex_lock(&philo->data->printer);
		// if (is_not_dead(philo->data))
			printf("%lli %i is sleeping\n",
				get_time() - philo->data->start_time, philo->id);
		// pthread_mutex_unlock(&philo->data->printer);
		// if (is_not_dead(philo->data))
			usleep(philo->data->time_to_sleep * 1000);
	}
}

void	philo_think(t_philo *philo)
{
	if (is_not_dead(philo->data))
	{
		// pthread_mutex_lock(&philo->data->printer);
		// if (is_not_dead(philo->data))
			printf("%lli %i is thinking\n",
				get_time() - philo->data->start_time, philo->id);
		// pthread_mutex_unlock(&philo->data->printer);
	}
}
	