/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysemlali <ysemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:23:01 by ysemlali          #+#    #+#             */
/*   Updated: 2024/10/15 12:23:01 by ysemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (-1);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	return (result * sign);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	custom_sleep(size_t duration)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < duration)
		usleep(100);
}

void	print_status(t_philo *philo, char *status)
{
	t_state	*state;

	state = philo->state;
	pthread_mutex_lock(&state->write);
	if (!state->someone_died)
		printf("%zu %d %s\n", get_time() - state->starttime, philo->id, status);
	pthread_mutex_unlock(&state->write);
}

void	error(int out, char *msg)
{
	if (out != 0)
	{
		while (*msg)
			write(2, msg++, 1);
		write(2, "\n", 1);
		exit(1);
	}
}
