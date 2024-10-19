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

int	alive(t_ph *ph)
{
	lock(ph->d);
	if (*ph->died)
		return (unlock(ph->d), 1);
	unlock(ph->d);
	return (0);
}

void	message(t_ph *ph, char *message)
{
	lock(ph->w);
	if (alive(ph) == 0)
		printf("%zu %d %s\n", ft_time() - ph->start, ph->i, message);
	unlock(ph->w);
}

void	*eat(t_ph *ph)
{
	lock(ph->fork_l);
	message(ph, "has taken a fork");
	if (ph->n == 1)
		return (ft_usleep(ph->die), unlock(ph->fork_r), NULL);
	lock(ph->fork_l);
	message(ph, "has taken a fork");
	ph->eating = 1;
	message(ph, "is eating");
	lock(ph->m);
	ph->last_m = ft_time();
	ph->meals_i++;
	unlock(ph->m);
	ft_usleep(ph->eat);
	return (ph->eating = 0, unlock(ph->fork_l), unlock(ph->fork_r), NULL);
}

int	cycle(t_ph *ph)
{
	if (alive(ph))
		return (1);
	eat(ph);
	message(ph, "is sleeping");
	ft_usleep(ph->sleep);
	message(ph, "is thinking");
	return (0);
}
