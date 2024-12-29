/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:00:38 by ysemlali          #+#    #+#             */
/*   Updated: 2024/10/15 00:00:38 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alive(t_ph *ph)
{
	lock(ph->d);
	if (*ph->died)
		return (unlock(ph->d), 1);
	unlock(ph->d);
	return (0);
}

int	done(t_ph *ph)
{
	if (ph->meals == -1)
		return (0);
	lock(ph->m);
	if (ph->times >= (size_t)ph->meals)
	{
		*ph->s_done += 1;
		ph->done = 1;
		unlock(ph->m);
		return (1);
	}
	return (unlock(ph->m), 0);
}

void	*run(void *p)
{
	t_ph	*ph;

	ph = (t_ph *)p;
	if (ph->i % 2 == 0)
		usleep((ph->eat * 1000));
	if (ph->n == 1)
		return (lock(ph->fork_r), message(ph, "has taken a fork"),
			usleep(ph->eat * 1000), NULL);
	while (1)
	{
		cycle(ph);
		if (alive(ph) || (done(ph)))
			break ;
	}
	return (p);
}

void	init_threads(pthread_t *monitor, t_state *s)
{
	int	i;

	i = 0;
	(void)monitor;
	if (error(pthread_create(monitor, NULL, &observe, s), 1, s))
		return ;
	while (i < s->n)
	{
		if (error(pthread_create(&s->ph[i].p, NULL, &run, &s->ph[i]), 1, s))
			return ;
		i++;
	}
	i = 0;
	while (i < s->n)
		if (error(pthread_join(s->ph[i++].p, NULL), 2, s))
			return ;
	if (error(pthread_join(*monitor, NULL), 2, s))
		return ;
}
