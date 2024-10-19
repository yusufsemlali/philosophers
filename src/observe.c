/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:48:05 by ysemlali          #+#    #+#             */
/*   Updated: 2024/10/15 00:48:05 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	running(t_state *s)
{
	int	finished;

	finished = 0;
	if (s->meals == -1)
		return (0);
	while (s->n--)
	{
		lock(s->ph[s->n].m);
		if (s->ph[s->n].meals_i >= s->meals)
			finished++;
		unlock(s->ph[s->n].m);
	}
	if (finished == s->n)
		return (lock(s->ph[0].m), s->ph[0].died = 0, unlock(s->ph[0].m), 1);
	s->n = s->ph[0].meals;
	return (0);
}

int	died(t_ph *ph)
{
	lock(ph->m);
	if (ft_time() - ph->last_m >= ph->die && ph->eating == 0)
		return (unlock(ph->m), 1);
	return (unlock(ph->m), 0);
}

void	*observe(void *p)
{
	t_state	*s;
	int		i;

	i = 0;
	s = (t_state *)p;
	while (1)
	{
		while (i < s->n)
		{
			if (died(&s->ph[i]))
				return (message(&s->ph[i], "died"), lock(s->ph[i].d),
					*s->ph[i].died = 1, unlock(s->ph[i].d), NULL);
			if (running(s))
				return (lock(s->ph[i].d), *s->ph[i].died = 1,
					unlock(s->ph[i].d), NULL);
			i++;
		}
	}
	return (p);
}
