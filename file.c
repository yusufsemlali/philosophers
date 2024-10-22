#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 200

typedef struct
{
	int				id;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				*forks;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	*print_mutex;
	long long		start_time;
	long long		last_meal_time;
	int				meals_eaten;
	int				*someone_died;
}					philosopher_t;

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

void	print_status(philosopher_t *philo, const char *status)
{
	pthread_mutex_lock(philo->print_mutex);
	if (!(*philo->someone_died))
	{
		printf("%lld %d %s\n", get_time() - philo->start_time, philo->id,
			status);
	}
	pthread_mutex_unlock(philo->print_mutex);
}

void	take_forks(philosopher_t *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->num_philosophers;
	pthread_mutex_lock(&philo->fork_mutexes[left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_mutexes[right_fork]);
	print_status(philo, "has taken a fork");
}

void	put_down_forks(philosopher_t *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->num_philosophers;
	pthread_mutex_unlock(&philo->fork_mutexes[left_fork]);
	pthread_mutex_unlock(&philo->fork_mutexes[right_fork]);
}

void	*philosopher_routine(void *arg)
{
	philosopher_t	*philo;

	philo = (philosopher_t *)arg;
	while (!(*philo->someone_died) && (philo->meals_to_eat == -1
			|| philo->meals_eaten < philo->meals_to_eat))
	{
		take_forks(philo);
		print_status(philo, "is eating");
		philo->last_meal_time = get_time();
		usleep(philo->time_to_eat * 1000);
		put_down_forks(philo);
		philo->meals_eaten++;
		print_status(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	philosopher_t	*philosophers;

	philosophers = (philosopher_t *)arg;
	int i, all_ate_enough;
	while (1)
	{
		all_ate_enough = 1;
		for (i = 0; i < philosophers[0].num_philosophers; i++)
		{
			if (get_time()
				- philosophers[i].last_meal_time > philosophers[i].time_to_die)
			{
				print_status(&philosophers[i], "died");
				*philosophers[i].someone_died = 1;
				return (NULL);
			}
			if (philosophers[i].meals_to_eat != -1
				&& philosophers[i].meals_eaten < philosophers[i].meals_to_eat)
				all_ate_enough = 0;
		}
		if (philosophers[0].meals_to_eat != -1 && all_ate_enough)
			return (*philosophers[0].someone_died = 1, NULL);
		usleep(1000);
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s <num_philosophers>", argv[0]);
		printf(" <time_to_die> <time_to_eat> <time_to_sleep> [meals_to_eat]\n");
		return (1);
	}

	int num_philosophers = atoi(argv[1]);
	int time_to_die = atoi(argv[2]);
	int time_to_eat = atoi(argv[3]);
	int time_to_sleep = atoi(argv[4]);
	int meals_to_eat = (argc == 6) ? atoi(argv[5]) : -1;

	if (num_philosophers <= 0 || num_philosophers > MAX_PHILOSOPHERS
		|| time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0
		|| (argc == 6 && meals_to_eat <= 0))
		return (printf("Invalid arguments\n"), 1);

	philosopher_t philosophers[MAX_PHILOSOPHERS];
	pthread_t threads[MAX_PHILOSOPHERS];
	pthread_mutex_t fork_mutexes[MAX_PHILOSOPHERS];
	pthread_mutex_t print_mutex;
	int forks[MAX_PHILOSOPHERS] = {0};
	int someone_died = 0;

	pthread_mutex_init(&print_mutex, NULL);
	for (int i = 0; i < num_philosophers; i++)
		pthread_mutex_init(&fork_mutexes[i], NULL);
	long long start_time = get_time();
	for (int i = 0; i < num_philosophers; i++)
	{
		philosophers[i] = (philosopher_t){.id = i + 1,
			.num_philosophers = num_philosophers, .time_to_die = time_to_die,
			.time_to_eat = time_to_eat, .time_to_sleep = time_to_sleep,
			.meals_to_eat = meals_to_eat, .forks = forks,
			.fork_mutexes = fork_mutexes, .print_mutex = &print_mutex,
			.start_time = start_time, .last_meal_time = start_time,
			.meals_eaten = 0, .someone_died = &someone_died};
		pthread_create(&threads[i], NULL, philosopher_routine,
			&philosophers[i]);
	}

	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, monitor_routine, philosophers);

	for (int i = 0; i < num_philosophers; i++)
		pthread_join(threads[i], NULL);
	pthread_join(monitor_thread, NULL);

	for (int i = 0; i < num_philosophers; i++)
		pthread_mutex_destroy(&fork_mutexes[i]);
	pthread_mutex_destroy(&print_mutex);

	return (0);
}