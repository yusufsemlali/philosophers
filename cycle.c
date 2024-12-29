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

void	*eat(t_ph *ph)
{
	if (ph->i % 2 == 0)
	{
		lock(ph->fork_l);
		message(ph, "has taken a fork");
		lock(ph->fork_r);
		message(ph, "has taken a fork");
	}
	else
	{
		lock(ph->fork_r);
		message(ph, "has taken a fork");
		lock(ph->fork_l);
		message(ph, "has taken a fork");
	}
	{
		lock(ph->m);
		ph->eating = 1;
		ph->last_m = ft_time();
		unlock(ph->m);
	}
	message(ph, "is eating");
	usleep(ph->eat * 1000);
	unlock(ph->fork_r);
	unlock(ph->fork_l);
	lock(ph->m);
	ph->meals_i++;
	ph->eating = 0;
	unlock(ph->m);
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
		return (unlock(ph->fork_r), p);
	}
	while (1)
	{
		if (alive(ph) == 0)
			break ;
		eat(ph);
		if (alive(ph) == 0)
			break ;
		message(ph, "is sleeping");
		usleep(ph->sleep * 1000);
		if (alive(ph) == 0)
			break ;
		message(ph, "is thinking");
	}
	return (p);
}
