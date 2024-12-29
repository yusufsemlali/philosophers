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

int	died(t_ph *ph)
{
	lock(ph->m);
	if (ph->done == 0 && ft_time() - ph->last_m > ph->die && ph->eating == 0)
		return (unlock(ph->m), 1);
	return (unlock(ph->m), 0);
}

int	complete(t_state *state)
{
	lock(&state->m);
	if (state->s_done == state->n)
		return (unlock(&state->m), 1);
	return (unlock(&state->m), 0);
}

void	*observe(void *p)
{
	t_state	*s;
	int		i;

	s = (t_state *)p;
	while (1)
	{
		i = 0;
		while (i < s->n)
		{
			if (died(&s->ph[i]))
				return (message(&s->ph[i], "died"), lock(s->ph[i].d),
					*s->ph[i].died = 1, unlock(s->ph[i].d), p);
			if (complete(s))
				return (p);
			usleep(1000);
			i++;
		}
	}
	return (p);
}
