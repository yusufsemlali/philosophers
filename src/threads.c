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

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_state	*state;

	philo = (t_philo *)arg;
	state = philo->state;
	if (philo->id % 2 == 0)
		custom_sleep(1);
	while (!state->someone_died && !state->finished)
	{
		pthread_mutex_lock(philo->leftfork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->rightfork);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->lastmeal = get_time();
		custom_sleep(state->timeto_eat);
		philo->eatcount++;
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->rightfork);
		print_status(philo, "is sleeping");
		custom_sleep(state->timeto_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_state	*s;
	int		i;

	s = (t_state *)arg;
	while (!s->someone_died && !s->finished)
	{
		i = 0;
		while (i < s->philocount)
		{
			if (get_time() - s->philos[i].lastmeal > (size_t)s->timeto_die)
			{
				print_status(&s->philos[i], "died");
				s->someone_died = 1;
				return (NULL);
			}
			if (s->musteat != -1
				&& s->philos[i].eatcount >= s->musteat)
				s->finished++;
			i++;
		}
		if (s->finished == s->philocount)
			return (NULL);
		custom_sleep(1);
	}
	return (NULL);
}
