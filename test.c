#include "./include/philosopher.h"

void	time_since_start(struct	timeval *time)
{
	struct	timeval time_now;
	long	sec;
	long	milli;

	usleep(5000000);
	gettimeofday(&time_now, 0) == 0;
	sec = time_now.tv_sec - time->tv_sec;
	milli = (time_now.tv_usec - time->tv_usec) / 1000;
	printf ("time passed since start = %li , %li\n", sec, milli);
}

void	main()
{
	long	time_milli;
	struct	timeval time;

	if (gettimeofday(&time, 0) == 0)
		time_milli = (time.tv_usec / 1000);
	printf ("time in micros = %li\n", time.tv_usec);
	printf ("time in ms = %li\n", time_milli);
	time_since_start(&time);
	return ;
}

/*
struct timeval current_time;
  gettimeofday(&current_time, NULL);
  */