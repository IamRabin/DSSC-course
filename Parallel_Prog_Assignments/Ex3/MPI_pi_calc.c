/**
 * Input : Number of steps (N)
 * Output: Integral estimation within interval of a to b using trapezoidal rule
 *
 * Algorithm:
 * 1. Each process have to figure out its interval for intergration.
 * 2. Each process estimates the interval  to perform integral.
 * 3. If I am not the last process, do the integration for local intervals.
 * 4. Perform reduce clause by the last process i.e. numprocs-1 .
 * 5. If I am the last process and also I am not the root ,send the reduced result to the root .
 * 6. If I am the root process and also I am not the last process , receive the result and print .
 */

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>



double midpoint(int start_point, int end_point, double h)
{
    double pi = 0.0;
    double x;

    for(int point = start_point; point< end_point; ++point)
    {
        x= point * h + h / 2.0;
        pi +=  h / (1 + x * x);
    }
    return 4 * pi;
}


////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////

int main(int argc,char *argv[])
{
     int myrank; //process rank
     int numprocs; // number of processes


    int N=atoi(argv[1]);


    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

    int master= 0 ; //
    int reduc=numprocs-1;// reduction api will be called in the last process


   double  t1=MPI_Wtime();

   double PI; // stores global Pi
   //double integral=0.0; //stores integral over the interval
   double h=1.0/N ; //width of each point over N
   int chunk_size=N/numprocs  ;// task for each process
   int local_start=chunk_size*myrank;
    int local_end=local_start+chunk_size;
    double integral = midpoint(local_start, local_end, h);

    //Add all the integrals calculated by each process
     MPI_Reduce(&integral, &PI, 1, MPI_DOUBLE, MPI_SUM, reduc, MPI_COMM_WORLD);
     double total_time = MPI_Wtime()-t1;



      //sending to print
      if(myrank == reduc)
      {
          MPI_Send(&PI, 1, MPI_DOUBLE, master, 101, MPI_COMM_WORLD);
      }

      // Receiving and printing job
      if(myrank == master )
      {
          MPI_Recv(&PI, 1, MPI_DOUBLE, reduc, 101, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          printf("Approximated value of Pi: %.6f\nElapsed_time: %.6f\n", PI, total_time);
      }
      MPI_Finalize();
      return 0;
  }
