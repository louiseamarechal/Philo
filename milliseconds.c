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
	struct timeval t1;
	struct timeval t2;

	gettimeofday(&t1, NULL);
	usleep(1000000);
	gettimeofday(&t2, NULL);
	printf("%ld\n", diff_time_in_msec(t2, t1));

	return (0);
}
