/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:50:28 by nrajabia          #+#    #+#             */
/*   Updated: 2023/08/17 16:21:29 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	set_forks_state(t_philo *philo, bool state)
{
	pthread_mutex_lock (&philo->r_fork->mutex);
	philo->r_fork->taken = state;
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_lock(&philo->l_fork->mutex);
	philo->l_fork->taken = state;
	pthread_mutex_unlock(&philo->l_fork->mutex);
}

void	routine(t_philo *philo)
{
	philo->life_time = get_time() + philo->data->time_to_die;
	set_forks_state(philo, true);
	message(philo, R_FORK);
	message(philo, L_FORK);
	message(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	set_forks_state(philo, false);
	pthread_mutex_lock(&philo->data->checker);
	if (++philo->eat_counter >= philo->data->nb_of_meals)
		philo->data->nb_of_finished++;
	pthread_mutex_unlock(&philo->data->checker);
	message(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
}

void	start_day(t_philo *philo)
{
	if (!philo->l_fork)
		return ;
	pthread_mutex_lock(&philo->data->checker);
	pthread_mutex_lock(&philo->r_fork->mutex);
	if (!philo->r_fork->taken)
	{
		pthread_mutex_unlock(&philo->r_fork->mutex);
		pthread_mutex_lock(&philo->l_fork->mutex);
		if (!philo->l_fork->taken)
		{
			pthread_mutex_unlock(&philo->l_fork->mutex);
			pthread_mutex_unlock(&philo->data->checker);
			routine(philo);
			message(philo, THINK);
			return ;
		}
		else
			pthread_mutex_unlock(&philo->l_fork->mutex);
	}
	else
		pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_unlock(&philo->data->checker);
}
