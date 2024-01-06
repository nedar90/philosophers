/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:14:22 by nrajabia          #+#    #+#             */
/*   Updated: 2023/08/17 16:18:35 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	destroy_mutex(t_data *data, int size, int flag)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->checker);
	if (flag == 2)
		while (--size)
			pthread_mutex_destroy(&data->forks[size].mutex);
	free(data->philos);
	free(data->forks);
}

int	ft_error(t_data *data, char *err, int size, int flag)
{
	printf("Error: %s\n", err);
	if (flag != 0)
		destroy_mutex(data, size, flag);
	return (1);
}

void	message(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->start_time;
	if (msg[0] == 'd' && !philo->data->dead)
	{
		printf("%li %d %s\n", time, philo->id, msg);
		philo->data->dead = true;
	}
	if (!philo->data->dead)
		printf("%li %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

int	check_input(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		if ((i == 2 && j > 13) || (i == 3 && j > 13) || (i == 4 && j > 13))
			return (1);
	}
	return (0);
}

long	ft_atoi(const char *nptr)
{
	int		sign;
	long	number;

	sign = 1;
	number = 0;
	while (*nptr == ' '
		|| (*nptr >= 10 && *nptr <= 13)
		|| *nptr == '\t')
		nptr++;
	if (*nptr == '-')
		sign *= -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		number = number * 10 + *nptr - 48;
		nptr++;
	}
	return (sign * number);
}
