/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:03:29 by ysemlali          #+#    #+#             */
/*   Updated: 2024/10/14 23:58:30 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_state(t_state *state, char **av, int i)
{
	state->philocount = ft_atoi(av[1]);
	state->timeto_die = ft_atoi(av[2]);
	state->timeto_eat = ft_atoi(av[3]);
	state->timeto_sleep = ft_atoi(av[4]);
	state->musteat = ft_atoi(av[5]);
	state->finished = 0;
	state->someone_died = 0;
	state->starttime = get_time();
	pthread_mutex_init(&state->write, NULL);
	pthread_mutex_init(&state->meal, NULL);
	while (i < state->philocount)
		pthread_mutex_init(&state->forks[i++], NULL);
}

void	init_philos(t_state *state, int i)
{
	while (i < state->philocount)
	{
		state->philos[i].id = i + 1;
		state->philos[i].eatcount = 0;
		state->philos[i].lastmeal = state->starttime;
		state->philos[i].leftfork = &state->forks[i];
		state->philos[i].rightfork = &state->forks[(i + 1) % state->philocount];
		state->philos[i++].state = state;
	}
}
