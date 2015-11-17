#include <mpi.h>
#include <stdio.h>
// #include <iostream>

// using namespace std;

int main (int argc, char* argv[])
{
  int rank, size;
  MPI_Init (&argc, &argv);      /* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */

	int number;
  number = 11;
	
  MPI_Send(&number, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
  printf("rank_outside: %d \n", rank);
  if(rank == 0){
  	MPI_Recv(&number, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
  	printf("Process %d received number %d from process %d\n",
		           0, number,size-1); 	
  }

	if (rank > 0) {
		printf("rank: %d \n", rank);
		if(size == rank-1){
			MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}

		else{
    	MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);			
   		printf("Process %d received number %d from process %d\n",
		           rank, number,rank-1); 	
    }

    // if (! rank == 0){
    // }
       
	}

	MPI_Finalize();
	return 0;

}
