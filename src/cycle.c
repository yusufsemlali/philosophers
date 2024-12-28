/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:18:13 by ysemlali          #+#    #+#             */
/*   Updated: 2024/10/15 10:05:16 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_ph *ph, char *message)
{
	lock(ph->w);
	if (alive(ph) == 0)
		printf("%zu %d %s %d\n", ft_time() - ph->start, ph->i, message, ph->i
			% 2);
	unlock(ph->w);
}

void	take_forks(t_ph *ph)
{
	if (ph->i % 2 == 0)
	{
		lock(ph->fork_r);
		message(ph, "has taken a fork");
		lock(ph->fork_l);
		message(ph, "has taken a fork");
	}
	else
	{
		lock(ph->fork_l);
		message(ph, "has taken a fork");
		lock(ph->fork_r);
		message(ph, "has taken a fork");
	}
}

int	eat(t_ph *ph)
{
	take_forks(ph);
	lock(ph->m);
	ph->eating = 1;
	ph->last_m = ft_time();
	ph->times++;
	unlock(ph->m);
	message(ph, "is eating");
	usleep(ph->eat * 1000);
	lock(ph->m);
	ph->eating = 0;
	unlock(ph->m);
	unlock(ph->fork_l);
	unlock(ph->fork_r);
	return (0);
}

int	cycle(t_ph *ph)
{
	eat(ph);
	message(ph, "is sleeping");
	usleep(ph->sleep * 1000);
	message(ph, "is thinking");
	/*usleep(700);*/
	return (0);
}
