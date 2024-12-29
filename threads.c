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

void	init_threads(t_state *s)
{
	int	i;

	i = 0;
	while (i < s->n)
	{
		if (error(pthread_create(&s->ph[i].p, NULL, &cycle, &s->ph[i]), 1, s))
			return ;
		i++;
	}
	i = 0;
	while (i < s->n)
		if (error(pthread_join(s->ph[i++].p, NULL), 2, s))
			return ;
}

void	init_observers(pthread_t *death, pthread_t *meals, t_state *s)
{
  if (s->n > 1)
  {

    if (error(pthread_create(death, NULL, &observer_d, s), 1, s))
      return ;
    if (s->meals != -1)
    {
      if (error(pthread_create(meals, NULL, &observer_m, s), 1, s))
        return ;
    }
	if (error(pthread_join(*death, NULL), 2, s))
		return ;
	if (error(pthread_join(*meals, NULL), 2, s))
		return ;
  }
}
