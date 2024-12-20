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

int	valid(char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > MAX_PH || ft_isalnum(av[1]))
		return (ft_write("number of philosophers is invalid", 2), 1);
	if (ft_atoi(av[2]) <= 0 || ft_isalnum(av[2]))
		return (ft_write("time to die is invalid", 2), 1);
	if (ft_atoi(av[3]) <= 0 || ft_isalnum(av[3]))
		return (ft_write("time to eat is invalid", 2), 1);
	if (ft_atoi(av[4]) <= 0 || ft_isalnum(av[4]))
		return (ft_write("time to sleep is invalid", 2), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || ft_isalnum(av[5])))
		return (ft_write("number of meals is invalid", 2), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_ph		ph[200];
	t_state		state;
	pthread_t	monitor;

	if (ac != 5 && ac != 6)
		return (ft_write("wrong number of arguments", 2), 1);
	if (valid(av))
		return (1);
	init(ph, init_state(&state, av, ph));
	init_threads(&monitor, &state);
}
