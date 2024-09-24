
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

int	error(int err, int type)
{
	if (err != 0)
	{
		if (type == 1)
			return (printf("thread creation error\n"), 1);
		else if (type == 2)
			return (printf("thread join error\n"), 1);
		else if (type == 3)
			return (printf("thread died\n"), 1);
		else if (type == 4){
			return (printf("done eating\n"), 1);
                        exit(0);
        }
                        
		else if (type == 5)
			return (printf("done sleeping\n"), 1);
	}
	return (0);
}

long long	ft_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}
