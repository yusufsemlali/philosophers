# ifndef PHILO
#define PHILO


# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define SIZE 1024



// typedef struct s_thread
// {
//     pthread_t        *thread;
//     pthread_attr_t *attr;
//     void            *arg;
// } t_thread;


typedef struct s_philo
{
    size_t      n;
    size_t      die;
    size_t      eat;
    size_t      sleep;
    size_t      times;
    size_t      died;
    size_t      counter;
}  t_philo;



typedef struct s_th
{
    pthread_t       p;
    size_t          f;
    size_t          t;
    pthread_mutex_t mx;
    t_philo  *ph;
    struct s_th     *next;
}t_th;


long    ft_atoi(const char *str);
int     error(int err, int type);
long    long ft_time();



#endif