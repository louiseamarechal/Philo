#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long int	diff_time_in_msec(struct timeval t1, struct timeval t2)
{
	long int diff;

	diff = 0;
	diff += (t1.tv_sec - t2.tv_sec) * 1000;
	diff += (t1.tv_usec - t2.tv_usec) / 1000;
	return (diff);
}

int	main(void)
{
	// struct timeval current_time; // structure definit par sys.time.h
	// int	start_time;
	// int	action_time;
	//
	// start_time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	// gettimeofday(&current_time, NULL);
	// printf("seconds = %ld\nmicro seconds = %ld\n", current_time.tv_sec, current_time.tv_usec);
	// printf("seconds since 1970 en microsecond = %ld\n", current_time.tv_sec * 1000000);
	// printf("seconds + micro = %ld\n", (current_time.tv_sec * 1000000)+ current_time.tv_usec);
	// printf("millisecond since 1970 = %ld\n", ((current_time.tv_sec * 1000000)+ current_time.tv_usec) / 1000);

	// ((start_sec - act_sec) * 1000) + ((start_microsec - act_microsec) / 1000)
	// 1 microsecond == 0,001 millisecond

	struct timeval t1;
	struct timeval t2;

	gettimeofday(&t1, NULL);
	usleep(1000000);
	gettimeofday(&t2, NULL);
	printf("%ld\n", diff_time_in_msec(t2, t1));

	return (0);
}
