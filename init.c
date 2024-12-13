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

#include "state->pilo.h"

t_state	*init_state(t_state state[MAX_PH], char **av)
{
	int	i;

	i = 0;
	state[0].n = ft_atoi(av[1]);
	state[0].die = ft_atoi(av[2]);
	state[0].eat = ft_atoi(av[3]);
	state[0].sleep = ft_atoi(av[4]);
	state[0].meals = -1;
	if (av[5])
		state[0].meals = ft_atoi(av[5]);
	state[0].death_state = 0;
	pthread_mutex_init(&state[0].d, NULL);
	pthread_mutex_init(&state[0].w, NULL);
	pthread_mutex_init(&state[0].m, NULL);
	while (i < state[0].n)
		pthread_mutex_init(&state[0].fork[i++], NULL);
	return (state);
}

void	init(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->n)
	{
		state[i]->i = i + 1;
		state->n = state->n;
		state->die = state->die;
		state->eat = state->eat;
		state->sleep = state->sleep;
		state->meals = state->meals;
		state->p[i].meals_i = 0;
		state->p[i].died = &state->death_state;
		state->p[i].d = &state->d;
		state->p[i].w = &state->w;
		state->p[i].m = &state->m;
		state->p[i].start = ft_time();
		state->p[i].last_m = ft_time();
		state->p[i].fork_r = &state->fork[i];
		state->p[i].fork_l = &state->fork[(i +1)% state->n];
		i++;
	}
}
