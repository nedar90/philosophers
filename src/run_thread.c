/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:19:19 by nrajabia          #+#    #+#             */
/*   Updated: 2023/08/17 16:20:29 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	philos_checker(t_philo *philo)
{
	if (philo->life_time <= get_time())
	{
		message(philo, DIED);
		return (1);
	}
	if ((philo->data->nb_of_finished >= philo->data->nb_of_philos
			&& philo->data->nb_of_meals > 0))
	{
		philo->data->dead = true;
		return (1);
	}
	return (0);
}

void	*action(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->data->checker);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->checker);
			break ;
		}
		pthread_mutex_unlock(&philo->data->checker);
		pthread_mutex_lock(&philo->data->checker);
		if (philos_checker(philo))
		{
			pthread_mutex_unlock(&philo->data->checker);
			return ((void *)0);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->checker);
			start_day(philo);
		}
	}
	return ((void *)0);
}

int	run_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philos)
	{
		if (pthread_create(&data->philos[i].tid, NULL,
				&action, (void *)&data->philos[i]))
			return (ft_error(data, CR_THREAD,
					data->nb_of_philos, FULL_DESTROY));
		ft_usleep(1);
	}
	while (i--)
		if (pthread_join(data->philos[i].tid, NULL))
			return (ft_error(data, J_THREAD, data->nb_of_philos, FULL_DESTROY));
	return (0);
}
