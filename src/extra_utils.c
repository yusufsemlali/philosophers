/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:23:46 by ysemlali          #+#    #+#             */
/*   Updated: 2024/10/15 12:23:46 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_state *state)
{
	pthread_mutex_destroy(&state->w);
	pthread_mutex_destroy(&state->m);
	pthread_mutex_destroy(&state->d);
	while (state->n--)
		pthread_mutex_destroy(&state->fork[state->n]);
}

int	error(int err, int type, t_state *state)
{
	if (err != 0)
	{
		if (type == 1)
			return (destroy(state), ft_write("thread creation error\n", 2), 1);
		else if (type == 2)
			return (destroy(state), ft_write("thread join error\n", 2), 1);
	}
	return (0);
}

void	ft_write(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

void	lock(pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
}

void	unlock(pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
}
