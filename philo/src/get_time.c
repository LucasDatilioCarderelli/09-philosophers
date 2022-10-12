/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 02:58:12 by ldatilio          #+#    #+#             */
/*   Updated: 2022/10/13 01:44:31 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	pthread_mutex_t	tm;

	pthread_mutex_init(&tm, NULL);
	pthread_mutex_lock(&tm);
	gettimeofday(&tv, 0);
	pthread_mutex_unlock(&tm);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
