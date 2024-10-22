/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:53:26 by ysemlali          #+#    #+#             */
/*   Updated: 2024/10/15 09:33:07 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAXPHILO 200

typedef struct s_philo
{
	int				id;
	int				eatcount;
	size_t			lastmeal;
	pthread_t		thread;
	pthread_mutex_t	*leftfork;
	pthread_mutex_t	*rightfork;
	struct s_state	*state;
}					t_philo;

typedef struct s_state
{
	t_philo			philos[MAXPHILO];
	pthread_mutex_t	forks[MAXPHILO];
	pthread_mutex_t	write;
	pthread_mutex_t	meal;
	int				philocount;
	int				timeto_die;
	int				timeto_eat;
	int				timeto_sleep;
	int				musteat;
	int				finished;
	int				someone_died;
	size_t			starttime;
}					t_state;

// Initialization
void				init_state(t_state *state, char **av, int i);
void				init_philos(t_state *state, int i);

// Threads
void				*philo_routine(void *arg);
void				*monitor_routine(void *arg);

// Utils
long				ft_atoi(const char *str);
size_t				get_time(void);
void				custom_sleep(size_t duration);
void				print_status(t_philo *philo, char *status);
void				error(int out, char *msg);

#endif
