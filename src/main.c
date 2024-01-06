/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:20:16 by nrajabia          #+#    #+#             */
/*   Updated: 2023/08/17 16:16:12 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_error(NULL, ARG_E, 0, NO_DESTROY));
	if (check_input(av))
		return (ft_error(NULL, INPUT_E, 0, NO_DESTROY));
	if (init(&data, av, ac))
		return (1);
	if (run_thread(&data))
		return (1);
	destroy_mutex(&data, data.nb_of_philos, FULL_DESTROY);
	return (0);
}
