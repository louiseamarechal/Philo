#include "philosopher.h"

static long long int	diff_time_in_msec(long long int t1, long long int t2)
{
	// long long int diff;
	//
	// diff = t2 - t1;
	// diff += (t1.tv_sec - t2.tv_sec) * 1000;
	// diff += (t1.tv_usec - t2.tv_usec) / 1000;
	return (t2 - t1);
}

long long int	timestamp(void)
{
	struct timeval	time;
	long long int	timeofday;

	timeofday = 0;
	gettimeofday(&time, NULL);
	timeofday += time.tv_sec * 1000;
	timeofday += time.tv_sec / 1000;
	return (timeofday);
}

void	sleep_state(t_args *args, long long received_time)
{
	long long i;

	i = timestamp();
	while (args->died != 1)
	{
		if (diff_time_in_msec(i, timestamp()) >= received_time)
			break ;
		usleep(50);
		// printf("i = %lld\n", i);
		// printf("timestamp = %lld\n", timestamp());
		// printf("diff = %lld\n", diff_time_in_msec(i, timestamp()));
		// printf("recevied_time = %lld\n", received_time);
	}
}

void	print_state(t_args *args, int philo_id, char *state)
{
	long long i;

	i = timestamp();
	// pthread_mutex_lock(&args->prompt);
	if (args->died != 1)
		printf("%lld %d %s\n", i - args->first_timestamp, philo_id, state);
	// pthread_mutex_unlock(&args->prompt);
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
