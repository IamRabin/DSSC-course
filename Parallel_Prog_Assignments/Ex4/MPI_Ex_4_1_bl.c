#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>



int main(int argc, char* argv []){

    int N =atoi(argv[1]); //will convert  the first argument to an int when passed arguments on the command line.
    int nprocs,rank,chunk_size,rem;// #of processes, process id, work size, remainder
    int I; //column of the first entry
    int i,j,k;//row index,column index and index for the nprocs
    typedef int row [N];
    row* mat; //pointer to define integer datatype
    MPI_Status stat;

 //Environment Management Routines

    MPI_Init(&argc,&argv);// initialize MPI library
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);//Get number of tasks/processes running
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);//get id of each processes or tasks starting from 0 .

    chunk_size=N/nprocs ; //number of rows for each processor
    rem= N % nprocs; //the remaining rows.
    if(rank<rem)
    chunk_size++;

    /* For working space of local processors*/
    mat=(row*)malloc(chunk_size* sizeof (row));

    /* Column of the first entry*/

    I=chunk_size*rank;
    if (rank>=rem)
    I+=rem;

    /* Initializing the local matrix */

    for (i=0; i < chunk_size; i++)
    {
      for (j=0; j<N; j++)
        if (j == I)
          mat[i][j] = 1;
        else
          mat[i][j] = 0;
      I++;
    }

    if (rank!=0)
    {
        typedef int row [N];
        /* Send local data to Rank 0 */
        MPI_Send(mat, chunk_size*N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    else
    {
        if(N<10)
        {
            /* printing matrix */
             if (rank==0) //if rank is 0 print the local buffer
             {
                  for (i=0;i<chunk_size;i++)
                 {
                   for(j=0;j<N;j++)
                        printf("%d ", mat[i][j]);
                   printf("\n");
                 }

              /* Receiving data from other processes(np) inorder and print*/
            for (k=1; k < nprocs; k++)
             {
              if(k==rem)
              {
                chunk_size = chunk_size-1;
              }

              //status for the source of the message and the tag of the message
              MPI_Recv(mat, chunk_size*N, MPI_INT, k, 0, MPI_COMM_WORLD, &stat);
              for (i=0; i < chunk_size; i++)
                {
                  for (j=0; j<N; j++)
                     printf("%d ", mat[i][j]);
                     printf("\n");
                }

            }
            }

        }

        else //printing data to a file
        {
           FILE * data;
           data = fopen("identity_matrix.bin","wb");
           int * matrix= (int*) malloc(chunk_size* sizeof(int));

           for(int i = 0; i < nprocs; i++)
           {

               if(rank == 0)
                   // Write local matrix to file
                   fwrite(mat, sizeof(int), chunk_size*N, data);
               else
               {
                   // Receive process matrix and write it to file
                   MPI_Recv(matrix, chunk_size*N, MPI_INT, i, 111, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                   fwrite(matrix, sizeof(int), chunk_size*N, data);
               }
           }
           fclose(data);
           free(matrix);

        }

    }

         //done with MPI
          free(mat);
          MPI_Finalize();
          return 0;
        }
