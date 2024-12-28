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
	if (ft_time() - ph->last_m > ph->die && ph->eating == 0)
		return (unlock(ph->m), 1);
	return (unlock(ph->m), 0);
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
			if (died(&s->ph[i]) && s->ph[i].i % 2 != 0)
				return (message(&s->ph[i], "died"), lock(s->ph[i].d),
					*s->ph[i].died = 1, unlock(s->ph[i].d), NULL);
			usleep(1000);
			i++;
		}
	}
	return (p);
}
