#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <omp.h>

using namespace std;

int thread_count;
int n = 8;
int flag;
float sum=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void thread_sum(void* rank)
{
	
	/*long my_rank = (long) rank;
	double factor, my_sum = 0.0;
	long long i;
	long long my_n = n/thread_count;
	long long my_first_i = my_n * my_rank;
	long long my_last_i = my_first_i + my_n;*/
	double factor = 1.0;
	double my_sum = 0.0;
	# pragma omp parallel for num_threads(thread count) \
	reduction(+:my_sum)
	for(int i = 0; i < my_last_i; i++, factor = -factor){

		if(my_first_i % 2 == 0)
			factor = 1.0;
		else
			factor = -1.0;

		my_sum += factor/(2*i+1);
	}

	//while(flag != my_rank);
	/*pthread_mutex_lock(&mutex);
	sum += my_sum;
	pthread_mutex_unlock(&mutex);*/
	//flag = (flag + 1) % thread_count;

	return 0;
}

int main(int argc, char* argv[])
{
	/*long thread;
	pthread_t* thread_handles;
	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = (pthread_t* ) malloc(thread_count * sizeof(pthread_t));

	for(thread = 0; thread < thread_count; thread++)	
		pthread_create(&thread_handles[thread], NULL, thread_sum, (void*) thread);

	for(thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	cout<<"sum: "<<sum<<endl;*/

	double factor = 1.0;
	double my_sum = 0.0;
	int i;
	#pragma omp parallel for num_threads(thread count) \
	reduction(+:my_sum)
	for(i = 0; i < my_last_i; i++)
	{
		if(my_first_i % 2 == 0)
			factor = 1.0;
		else
			factor = -1.0;

		my_sum += factor/(2*i+1);
	}

	return 0;
}