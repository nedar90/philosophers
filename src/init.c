/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:26:54 by nrajabia          #+#    #+#             */
/*   Updated: 2023/08/17 16:17:39 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	mem_alloc(t_data *data)
{
	data->philos = (t_philo *)malloc(data->nb_of_philos * sizeof(t_philo));
	if (!data->philos)
		return (ft_error(NULL, MEM_E, 0, NO_DESTROY));
	memset(data->philos, 0, data->nb_of_philos * sizeof(t_philo));
	data->forks = (t_fork *)malloc(data->nb_of_philos * sizeof(t_fork));
	if (!data->forks)
	{
		free(data->philos);
		return (ft_error(NULL, MEM_E, 0, NO_DESTROY));
	}
	memset(data->forks, 0, data->nb_of_philos * sizeof(t_fork));
	return (0);
}

int	init_data(t_data *data, char **av, int ac)
{
	data->nb_of_philos = (int)ft_atoi(av[1]);
	data->time_to_die = (long)ft_atoi(av[2]);
	data->time_to_eat = (long)ft_atoi(av[3]);
	data->time_to_sleep = (long)ft_atoi(av[4]);
	data->start_time = get_time();
	if (data->start_time == -1)
		ft_error(NULL, TIME, 0, NO_DESTROY);
	data->nb_of_meals = 0;
	if (ac == 6)
		data->nb_of_meals = ft_atoi(av[5]);
	if (data->nb_of_philos < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| data->nb_of_meals < 0)
		return (ft_error(NULL, DATA_E, 0, NO_DESTROY));
	data->nb_of_finished = 0;
	data->dead = false;
	if (pthread_mutex_init(&data->print, NULL)
		|| pthread_mutex_init(&data->checker, NULL))
		return (ft_error(data, MUTEX_E, 0, MINI_DESTROY));
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_counter = -1;
		data->philos[i].life_time = get_time() + data->time_to_die;
		data->forks[i].taken = false;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
			return (ft_error(data, MUTEX_E, i, FULL_DESTROY));
		data->philos[i].r_fork = &data->forks[i];
		if (data->nb_of_philos == 1)
			data->philos[i].l_fork = NULL;
		else
			data->philos[i].l_fork = &data->forks[(i + 1) % data->nb_of_philos];
	}
	return (0);
}

int	init(t_data *data, char **av, int ac)
{
	if (init_data(data, av, ac))
		return (1);
	if (mem_alloc(data))
		return (1);
	if (init_philo(data))
		return (1);
	return (0);
}
