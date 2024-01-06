/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 08:52:13 by nrajabia          #+#    #+#             */
/*   Updated: 2023/08/16 16:44:06 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_H
# define LIBPHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

# define NO_DESTROY		0
# define MINI_DESTROY	1
# define FULL_DESTROY	2

# define ARG_E		"Wrong number of arguments."
# define INPUT_E	"None digit or too big number."
# define INIT_E		"Problem with initializing."
# define MUTEX_E	"Mutex fails to initialize."
# define DATA_E		"Data value"
# define MEM_E		"Memory allocating"
# define TIME		"We've got no time."
# define CR_THREAD	"Creation of the thread"
# define J_THREAD	"Joining of the thread"

# define R_FORK		"has taken a fork"
# define L_FORK		"has taken a fork"
# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK		"is thinking"
# define DIED		"died"

typedef struct s_fork
{
	bool				taken;
	pthread_mutex_t		mutex;
}	t_fork;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		tid;
	int				id;
	int				eat_counter;
	long			life_time;
	t_fork			*r_fork;
	t_fork			*l_fork;
}	t_philo;

typedef struct s_data
{
	int				nb_of_philos;
	int				nb_of_meals;
	int				nb_of_finished;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	bool			dead;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	checker;
	pthread_mutex_t	print;
}	t_data;

/*  utils  */
void	destroy_mutex(t_data *data, int size, int flag);
void	message(t_philo *philo, char *msg);
int		ft_error(t_data *data, char *err, int size, int flag);
int		check_input(char **av);
long	ft_atoi(const char *nptr);

/*  init  */
int		init(t_data *data, char **av, int ac);

/*  time  */
long	get_time(void);
void	ft_usleep(long time);

/*  run_thread  */
int		philos_checker(t_philo *philo);
int		run_thread(t_data *data);

/*  routine  */
void	start_day(t_philo *philo);

#endif
