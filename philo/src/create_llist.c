/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_llist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 01:10:31 by ldatilio          #+#    #+#             */
/*   Updated: 2022/10/10 07:12:27 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_llist(t_philo **philo)
{
	t_philo	*temp;

	temp = *philo;
	while (temp->next != *philo)
	{
		temp = temp->next;
		pthread_mutex_destroy(&temp->prev->fork);
		free(temp->prev);
	}
	pthread_mutex_destroy(&temp->fork);
	free(temp);
}

void	print_list(t_philo **philo)
{
	t_philo	*temp;

	temp = (*philo);
	while (1)
	{
		printf("print list id: %d\n", temp->id);
		temp = temp->next;
		if (temp == *philo)
			break ;
	}
}

static void	insert_back(t_philo **philo, t_philo **new_philo)
{
	t_philo	*temp;

	if (*philo == NULL)
	{
		(*new_philo)->next = (*new_philo);
		(*new_philo)->prev = (*new_philo);
		*philo = (*new_philo);
		return ;
	}
	temp = *philo;
	while (temp->next != *philo)
		temp = temp->next;
	temp->next = (*new_philo);
	(*new_philo)->next = *philo;
	(*new_philo)->prev = temp;
	(*philo)->prev = (*new_philo);
}

void	create_llist(t_data *data)
{
	int		i;
	t_philo	*new_philo;	

	i = 0;
	data->philo = NULL;
	while (++i <= data->number_of_philo)
	{
		new_philo = NULL;
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		new_philo->id = i;
		new_philo->data = data;
		new_philo->count_of_eat = 0;
		pthread_mutex_init(&new_philo->fork, NULL);
		insert_back(&data->philo, &new_philo);
	}
}
