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

t_state	*init_state(t_state *state, char **av, t_ph *ph)
{
	int	i;

	i = 0;
	state->ph = ph;
	state->n = ft_atoi(av[1]);
	state->die = ft_atoi(av[2]);
	state->eat = ft_atoi(av[3]);
	state->sleep = ft_atoi(av[4]);
	state->meals = -1;
	state->start = ft_time();
	if (av[5])
		state->meals = ft_atoi(av[5]);
	state->death_state = 0;
	pthread_mutex_init(&state->d, NULL);
	pthread_mutex_init(&state->w, NULL);
	pthread_mutex_init(&state->m, NULL);
	while (i < state->n)
		pthread_mutex_init(&state->fork[i++], NULL);
	return (state);
}

void	init(t_ph *ph, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->n)
	{
		ph[i].i = i + 1;
		ph[i].n = state->n;
		ph[i].die = state->die;
		ph[i].eat = state->eat;
		ph[i].sleep = state->sleep;
		ph[i].meals = state->meals;
		ph[i].meals_i = 0;
		ph[i].died = &state->death_state;
		ph[i].d = &state->d;
		ph[i].w = &state->w;
		ph[i].m = &state->m;
		ph[i].start = state->start;
		ph[i].last_m = state->start;
		ph[i].fork_r = &state->fork[i];
		ph[i].fork_l = &state->fork[(i + 1) % state->n];
		i++;
	}
}
