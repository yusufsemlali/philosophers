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
	int		i;
	int		sign;
	long	output;

	i = 0;
	sign = 1;
	output = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (output > (LONG_MAX - (str[i] - '0')) / 10)
			return (LONG_MAX);
		output *= 10;
		output += str[i] - '0';
		i++;
	}
	return (output * sign);
}

size_t	ft_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_write("gettimeofday() failed", 2);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t sleep_time)
{
	size_t	start;
	size_t	elapsed;
	size_t	remain;

	start = ft_time();
	while (1)
	{
		elapsed = ft_time() - start;
		if (elapsed >= sleep_time)
			break ;
		remain = sleep_time - elapsed;
		if (remain > 1000)
			usleep(1000);
		else if (remain > 100)
			usleep(100);
		else if (remain > 50)
			usleep(50);
		else
			usleep(10);
	}
}
