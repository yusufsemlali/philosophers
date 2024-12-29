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

# define RESET "\x1b[0m"
# define BOLD "\x1b[1m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define CYAN "\x1b[93m"
# define YELLOW "\x1b[36m"

# define SIZE 1024
# define MAX_PH 200

typedef struct s_ph
{
	pthread_t		p;
	size_t			eat;
	size_t			die;
	size_t			sleep;
	size_t			times;
	size_t			start;
	int				meals;
	size_t			last_m;
	size_t			eating;
	int				meals_i;
	int				*died;
	int				n;
	int				i;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*w;
	pthread_mutex_t	*d;
	pthread_mutex_t	*m;
}					t_ph;

typedef struct s_state
{
	t_ph			*ph;
	int				n;
	int				die;
	int				eat;
	int				sleep;
	int				death_state;
	int				meals;
	size_t			start;
	pthread_mutex_t	d;
	pthread_mutex_t	w;
	pthread_mutex_t	m[200];
	pthread_mutex_t	fork[200];

}					t_state;

// init
void				init(t_ph *ph, t_state *state);
t_state				*init_state(t_state *state, char **av, t_ph *ph);
void				init_fork(pthread_mutex_t *fork, int n);
void	init_threads(t_state *s);
void	init_observers(pthread_t *death, pthread_t *meals, t_state *s);

// threads
void	*observer_d(void *p);
void	*observer_m(void *p);
void				*cycle(void *p);
void				message(t_ph *ph, char *m);
int					alive(t_ph *ph);

// utils
size_t				ft_time(void);
void				ft_write(char *s, int fd);
void				ft_usleep(size_t sleep);
long				ft_atoi(const char *str);
int					error(int err, int type, t_state *state);
void				lock(pthread_mutex_t *mutex);
void				unlock(pthread_mutex_t *mutex);

#endif
