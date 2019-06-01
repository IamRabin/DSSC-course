
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>


 void main(int argc, char *argv[])
 {
   int myrank, nprocs, leftid, rightid;
   MPI_Status recv_status, send_status;
   MPI_Request send_request;

   /*----------------*/
   /* Initialize MPI */
   /*----------------*/

   MPI_Init(&argc, &argv);

   /*-------------------------------------------------------------------------------------------------------*/
   /* Find out my rank and size using global communicator MPI_COMM_WORLD          */
   /*--------------------------------------------------------------------------------------------------------*/

   MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
   MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

   /*--------------------*/
   /* Find out neighbors */
   /*--------------------*/

   if ((leftid=(myrank-1)) < 0) leftid = nprocs-1;
   if ((rightid=(myrank+1)) == nprocs) rightid = 0;

   /*---------------------------------------------------------------------*/
   /* Send the process rank stored as vec array to the process on my right and  */
   /* receive a process rank from the process on my left  */
   /*---------------------------------------------------------------------*/
   int N = atoi(argv[1]);

   /*----------------------------------*/
   /* Dynamic Allocation of  memory space  for large data elements*/
   /*---------------------------------*/
   int * vec = (int*)malloc(N * sizeof(int));
   int * recv = (int*)malloc(N * sizeof(int));
   int * sum = (int*)malloc(N * sizeof(int));

 // Populating my vector of size N with process rank
   for (int i = 0; i < N; ++i) {
      vec[i] = myrank;
      sum[i] = 0;
}

/*----------------------------------------------------------------------------------------------------------*/
/* sending - receivng elements  and tracking the sum of all the elements in the vector*/
/*-----------------------------------------------------------------------------------------------------------*/
       for (int i = 0; i < nprocs; ++i)
         {
             MPI_Issend(vec,N,MPI_INT,rightid,99,MPI_COMM_WORLD,&send_request);
             MPI_Recv(recv,N,MPI_INT,leftid,99,MPI_COMM_WORLD,&recv_status);
             MPI_Wait(&send_request,&send_status);
             for (int  i = 0; i < N; ++i) {
                 vec[i]=recv[i];
                 sum[i] += vec[i];
               }
           }
       /*--------------------------*/
       /* Print the output message */
       /*--------------------------*/

       printf("Proc %d sum = %d \n", myrank, sum[0]);

       /*-----------------------*/
       /* Exit and finalize MPI */
       /*-----------------------*/

       MPI_Finalize();

 }
