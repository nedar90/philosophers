/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:31:15 by saimar            #+#    #+#             */
/*   Updated: 2023/08/14 17:11:45 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

long	get_time(void)
{
	struct timeval	tv;
	int				err;

	err = gettimeofday(&tv, NULL);
	if (err)
		return (err);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}
