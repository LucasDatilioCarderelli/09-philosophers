/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:44:57 by ldatilio          #+#    #+#             */
/*   Updated: 2022/10/12 05:03:21 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **argv)
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || check_args(argv) == 1)
	{
		write(2, "ERROR: Invalid Arguments\n", 26);
		return (1);
	}
	(void) argv[0];
	data.dead = 0;
	data.number_of_philo = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data.number_of_eat = ft_atoi(argv[5]);
	else
		data.number_of_eat = -1;
	data.start_time = get_time();
	create_llist(&data);
	thread_init(&data);
	free_llist(&data.philo);
	return (0);
}
