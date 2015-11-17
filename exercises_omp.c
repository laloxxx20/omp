#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int ex_one(){
	#if _OPENMP >= 200805
    // I use tasks
    printf("_OPENMP >= 200805 (vers = %d)\n",_OPENMP);
	#else
	    // Tasks do not exist yet...
	    printf("_OPENMP < 200805 (vers = %d)\n",_OPENMP);
	#endif
	    return 0;
}

void Hello(void){
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	printf("Hello from thread %d of %d\n", my_rank, thread_count);
}

int main(int argc, char* argv[])
{
	ex_one();	
	return 0;
}