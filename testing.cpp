#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

int thread_count;
int n = 10;
int flag;
float sum=0;

void* thread_sum(void* rank)
{
	long my_rank = (long) rank;
	double factor, my_sum = 0.0;
	long long i;
	long long my_n = n/thread_count;
	long long my_first_i = my_n * my_rank;
	long long my_last_i = my_first_i + my_n;
	if(my_first_i % 2 == 0)
		factor = 1.0;
	else
		factor = -1.0;

	for(i = my_first_i; i < my_last_i; i++, factor = -factor)
		my_sum += factor/(2*i+1);

	while(flag != my_rank);
	sum += my_sum;
	flag = (flag + 1) % thread_count;

	return 0;
}

int main(int argc, char* argv[])
{
	long thread;
	pthread_t* thread_handles;
	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = (pthread_t* ) malloc(thread_count * sizeof(pthread_t));

	for(thread = 0; thread < thread_count; thread++)	
		pthread_create(&thread_handles[thread], NULL, thread_sum, (void*) thread);

	for(thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	cout<<"sum: "<<sum<<endl;

	return 0;
}