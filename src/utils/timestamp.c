#include "philosopher.h"

static long long int	diff_time_in_msec(long long int t1, long long int t2)
{
	long long int diff;

	diff = t2 - t1;
	// diff += (t1.tv_sec - t2.tv_sec) * 1000;
	// diff += (t1.tv_usec - t2.tv_usec) / 1000;
	return (diff);
}

long long int	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_sec / 1000);
}

void	sleep_state(t_args *args, long long time_to)
{
	long long i;

	i = timestamp();
	while (!(args->died))
	{
		if (diff_time_in_msec(i, timestamp()) >= time_to)
			break ;
		usleep(50);
	}
}

void	print_state(t_args *args, int philo_id, char *state)
{
	(void)args;
	// pthread_mutex_lock(&prompt);
	// if (args->died != 1)
		printf("%lld %d %s\n", timestamp(), philo_id, state);
	// pthread_mutex_unlock(&prompt);
}

// int	main(void)
// {
// 	struct timeval t1;
// 	struct timeval t2;
//
// 	gettimeofday(&t1, NULL);
// 	usleep(1000000);
// 	gettimeofday(&t2, NULL);
// 	printf("%ld\n", diff_time_in_msec(t2, t1));
//
// 	return (0);
// }
