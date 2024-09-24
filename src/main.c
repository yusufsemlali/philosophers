#include "philo.h"


int	eating(size_t eat, t_th *p)
{
	long long	start;

	printf("%zu is eating\n", p->f);
	start = ft_time();
	while (1)
		if (error(ft_sleep(start, (long long)eat), 4))
			return (1);
}

void	sleeping(size_t sleep, t_th *p)
{
	long long	start;

	printf("%zu is sleeping\n", p->f);
	start = ft_time();
	while (1)
		if (error(ft_sleep(start, (long long)sleep), 5))
			break ;
}

void	*run(void *th)
{
	t_th			*p;
	pthread_mutex_t	mx;
	long long		start;

	p = th;
	while (1)
	{
		start = ft_time();
        sleep(1);
		if (error((ft_time() - start) > p->t, 3))
			break ;
		// pthread_mutex_lock(&mx);
		// p->t -= eating(p->ph->eat, p);
		// printf("times left to eat for thread %zu: %zu \n", p->f, p->t);
		// sleeping(p->ph->sleep, p);
		// pthread_mutex_unlock(&mx);
	}
	return (pthread_mutex_destroy(&mx), NULL);
}

void	init(t_philo *ph)
{
	size_t	n;
	size_t	i;
	t_th	th[ph->n];

	n = ph->n;
	i = 0;
	if (n <= 200 && n > 0)
	{
		while (i < n)
		{
			th[i].f = i + 1;
			th[i].ph = ph;
			th[i].t = ph->times;
			if (i == 0)
			{
				th[n - 1].f = n - 1;
				th[i].next = &th[n - 1];
			}
			else
				th[i].next = &th[i - 1];
			error(pthread_create(&th[i].p, NULL, run, &th[i]), 1);
			i++;
		}
	}
	while (i-- > 1)
		error(pthread_join(th[i].p, NULL), 2);
}

int	main(int ac, char **av)
{
	t_philo ph;
	if (ac < 5 || ac > 6)
		return (0);

	ph.n = ft_atoi(av[1]);
	ph.die = ft_atoi(av[2]);
	ph.eat = ft_atoi(av[3]);
	ph.sleep = ft_atoi(av[4]);
	if (ac == 6)
		ph.times = ft_atoi(av[5]);
	init(&ph);
	sleep(1);
}