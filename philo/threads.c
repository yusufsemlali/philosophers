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

void	init_threads(pthread_t *monitor, t_state *s)
{
	int	i;

	i = 0;
	if (error(pthread_create(monitor, NULL, &observe, s), 1, s))
		return ;
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
