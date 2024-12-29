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

int	meals(t_state *s)
{
	int	finished;
	int	i;

	finished = 0;
	i = 0;
	printf("hello world\n");
	if (s->meals == -1)
		return (0);
	while (i < s->n)
	{
		lock(s->ph[i].m);
		if (s->ph[i].meals_i >= s->meals)
			finished++;
		unlock(s->ph[i].m);
	}
	if (finished == s->n)
		return (lock(&s->d), s->death_state = 1, unlock(&s->d), 1);
	return (0);
}

int	died(t_ph *ph)
{
	lock(ph->m);
	if (ft_time() - ph->last_m >= ph->die && ph->eating == 0)
		return (unlock(ph->m), 1);
	return (unlock(ph->m), 0);
}

void	*observer_d(void *p)
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
			{
				lock(s->ph[i].d);
				s->death_state = 1;
				printf("%s%s[ 🪪 %i died ] %s\n", YELLOW, BOLD, s->ph[i].i,
					RESET);
				unlock(s->ph[i].d);
				return (NULL);
			}
			usleep(1000);
			i++;
		}
	}
	return (p);
}

void	*observer_m(void *p)
{
	t_state	*s;
	int		i;

	s = (t_state *)p;
	while (1)
	{
		printf("hello world\n");
		i = 0;
		while (i < s->n)
		{
			if (meals(s))
				return (NULL);
			usleep(1000);
			i++;
		}
	}
	return (p);
}
