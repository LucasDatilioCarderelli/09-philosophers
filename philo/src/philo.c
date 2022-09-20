/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:44:57 by ldatilio          #+#    #+#             */
/*   Updated: 2022/09/20 03:16:47 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i] != NULL)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
		}
	}
	return (0);
}

void	insert_back(t_philo **philo, int id)
{
	t_philo	*new_philo;
	t_philo	*first;
	t_philo	*temp;

	new_philo = (t_philo *)malloc(sizeof(t_philo));
	new_philo->id = id;
	if (*philo == NULL)
	{
		new_philo->next = new_philo;
		new_philo->prev = new_philo;
		*philo = new_philo;
		return ;
	}
	first = *philo;
	temp = *philo;
	while (temp->next != first)
		temp = temp->next;
	temp->next = new_philo;
	new_philo->next = first;
	new_philo->prev = temp;
	first->prev = new_philo;
}

void	print_list(t_philo **philo)
{
	t_philo	*temp;
	t_philo	*first;

	temp = *philo;
	first = *philo;
	while (temp->next != first)
	{
		printf("print id: %d\n", temp->id);
		temp = temp->next;
	}
	printf("print id: %d\n", temp->id);
}

void	create_table(t_data *data)
{
	int		i;

	i = 0;
	data->philo = NULL;
	while (++i <= data->number_of_philo)
	{
		insert_back(&data->philo, i);
	}
	print_list(&data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || check_args(argv) == 1)
	{
		write(2, "ERROR: Invalid Arguments\n", 26);
		return (1);
	}
	(void) argv[0];
	data.number_of_philo = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data.number_of_eat = ft_atoi(argv[5]);
	else
		data.number_of_eat = -1;
	data.start_time = get_time();
	printf("number_of_philo: %d \n", data.number_of_philo);
	printf("time_to_die: %d \n", data.time_to_die);
	printf("time_to_eat: %d \n", data.time_to_eat);
	printf("time_to_sleep: %d \n", data.time_to_sleep);
	printf("number_of_eat: %d \n", data.number_of_eat);
	printf("start_time: %lld \n", data.start_time);
	create_table(&data);
	return (0);
}
