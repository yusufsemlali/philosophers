/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:03:10 by ysemlali          #+#    #+#             */
/*   Updated: 2024/10/14 23:57:40 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isalnum(char *s)
{
	while (*s)
	{
		if (*s < '0' && *s > '9')
			return (1);
		s++;
	}
	return (0);
}

int	valid(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (i == 1 && ft_atoi(av[i]) > MAXPHILO)
			return (0);
		if (ft_atoi(av[i]) <= 0 || ft_isalnum(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int			i;
	t_state		state;
	pthread_t	monitor_thread;

	i = 0;
	if (!valid(ac, av))
		return (printf("Invalid Input\n"), 1);
	init_state(&state, av, 0);
	init_philos(&state, 0);
	while (i < state.philocount)
	{
		error(pthread_create(&state.philos[i].thread, NULL, philo_routine,
				&state.philos[i]), "Thread Create Error");
		i++;
	}
	error(pthread_create(&monitor_thread, NULL, monitor_routine, &state),
		"Thread Create Error");
	i = 0;
	while (i < state.philocount)
		error(pthread_join(state.philos[i++].thread, NULL),
			"Thread Join Error");
	error(pthread_join(monitor_thread, NULL), "Thread Join Error");
	return (0);
}
