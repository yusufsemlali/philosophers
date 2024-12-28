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
	if (ph->meals != -1)
		if (ph->times >= (size_t)ph->meals)
			return (1);
	return (0);
}

void	*run(void *p)
{
	t_ph	*ph;

	ph = (t_ph *)p;
	if (ph->i % 2 == 0)
		usleep((ph->eat * 1000));
	while (!alive(ph) && !(done(ph)))
		cycle(ph);
	return (p);
}

void	init_threads(pthread_t *monitor, t_state *s)
{
	int	i;

	i = 0;
	while (i < s->n)
	{
		if (error(pthread_create(&s->ph[i].p, NULL, &run, &s->ph[i]), 1, s))
			return ;
		i++;
	}
	if (error(pthread_create(monitor, NULL, &observe, s), 1, s))
		return ;
	i = 0;
	while (i < s->n)
		if (error(pthread_join(s->ph[i++].p, NULL), 2, s))
			return ;
}
