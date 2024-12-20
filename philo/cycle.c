/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:18:13 by ysemlali          #+#    #+#             */
/*   Updated: 2024/12/16 01:11:46 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alive(t_ph *ph)
{
	lock(ph->d);
	if (*ph->died)
		return (unlock(ph->d), 0);
	unlock(ph->d);
	return (1);
}

void	message(t_ph *ph, char *m)
{
	lock(ph->w);
	if (alive(ph))
	{
		printf("%s[%zu ⏱️ ] %s[🪪 %d] %s%s %s\n", GREEN, ft_time() - ph->start,
			CYAN, ph->i, YELLOW, m, RESET);
	}
	unlock(ph->w);
}

void	*eat(t_ph *ph)
{
	{
		lock(ph->fork_r);
		message(ph, "has taken a fork");
		lock(ph->fork_l);
		message(ph, "has taken a fork");
		message(ph, "is eating");
		ft_usleep(ph->eat);
		unlock(ph->fork_r);
		unlock(ph->fork_l);
	}
  {
    lock(ph->m);
    ph->last_m = ft_time();
    ph->meals_i++;
    unlock(ph->m);
	}
  return (NULL);
}

void	*cycle(void *p)
{
	t_ph	*ph;

	ph = (t_ph *)p;
	if (ph->i % 2 == 0)
		ft_usleep(10);
	if (ph->n == 1)
	{
		lock(ph->fork_l);
		message(ph, "has taken a fork");
		return (usleep(ph->die), unlock(ph->fork_r), p);
	}
	while (alive(ph))
	{
    eat(ph);
		message(ph, "is sleeping");
		ft_usleep(ph->sleep);
		message(ph, "is thinking");
	}
	return (p);
}
