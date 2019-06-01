
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main (int argc, char* argv[]){

    int myrank, nprocs, left, right, count; //current process rank, #of processes, left to current, right to curent
    MPI_Status status;

    float val;
    float recv;
    float sum;
/*----------------*/
 /* Initialize MPI */
 /*----------------*/
    MPI_Init(&argc, &argv);

/*--------------------------------------------------------------------*/
/* Find out my rank and size using global communicator MPI_COMM_WORLD */
/*--------------------------------------------------------------------*/

    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    /* Initialize workspace */
    val   = myrank;
    recv   = -1;
    sum = val;

    /* Compute neighbour ranks */
    right = (myrank+1)%nprocs;
    left  = (myrank-1+nprocs)%nprocs;

    /* Circular sum*/
    for(count = 1; count < nprocs; count++)
      {
    MPI_Sendrecv(&val, 1, MPI_FLOAT, left, 0,
                             &recv, 1, MPI_FLOAT, right, 0,
                              MPI_COMM_WORLD, &status);
    /* Set "val" value to the newly received rank */
    val =recv;
    /* Update the partial sum */
    sum += val;
      }
    printf("\tI am proc %d and sum = %1.2f \n", myrank, sum);

    MPI_Finalize();

}
