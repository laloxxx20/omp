#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;
 
void* print_message_function( void* ptr )
{
     char* message;
     message = (char *) ptr;
     printf("%s \n", message);
}


void creating_matrix(vector< vector<int> >& matrix, int size_square)
{
	srand (time(NULL));
	for(int i=0; i<size_square; i++)
	{
		vector<int> v;
		matrix.push_back(v);
		for(int j=0; j<size_square; j++)
			matrix[i].push_back(rand() % 100 + 1);
	}
}


void print_matrix(vector< vector<int> >& matrix)
{	
	for(int i=0; i<matrix.size(); i++)
	{
		for(int j=0; j<matrix[i].size(); j++)
			cout<<matrix[i][j]<<" ";
	
		cout<<endl;
	}	
}


void print_v(vector<int>& v)
{	
	for(int i=0; i<v.size(); i++)
	{		
		cout<<v[i]<<" ";		
	}	
}

void create_vector(vector<int>& v, int size_v)
{
	for(int i=0; i<size_v; i++)
		v.push_back(i);
}


void send_to_thread(void* v /*, vector<int> v*/)
{
	cout<<endl;
	vector<int> v_ready = (vector<int>) v;
	print_v(v_ready);
	vector<int> unique; 
	create_vector(unique, 5);
	for(int i=0; i<v_ready.size(); i++)
		cout<<i<<": "<<v_ready[i]*unique[i]<<endl;
}


int main()
{

	vector<vector<int> > matrix;
	creating_matrix(matrix, 5);
	print_matrix(matrix);

	for(int i=0; i<matrix.size(); i++)
	{
		pthread_t thread;
	    pthread_create( &thread, NULL, send_to_thread, (void*) matrix[i]);
	    pthread_join( thread, NULL);

	}
 
	// pthread_t thread1, thread2;
	// const char *message1 = "Thread 1";
	// const char *message2 = "Thread 2";
	// int  iret1, iret2;

    /* Create independent threads each of which will execute function */
 
     // iret1 = pthread_create( &thread1, NULL, print_message_function, (void*) message1);
     // if(iret1)
     // {
     //     fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
     //     exit(EXIT_FAILURE);
     // }
 
     // iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);
     // if(iret2)
     // {
     //     fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
     //     exit(EXIT_FAILURE);
     // }
 
     // printf("pthread_create() for thread 1 returns: %d\n",iret1);
     // printf("pthread_create() for thread 2 returns: %d\n",iret2);
 
     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */
 
     // pthread_join( thread1, NULL);
     // pthread_join( thread2, NULL);
 
    exit(EXIT_SUCCESS);
	return 0;
}
 
