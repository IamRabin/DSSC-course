#include <stdio.h>
#include "gputimer.h"

const int N=8192;  //matrix size of N*N
const int k=8;     //tile size is  N*N
const int repetiton=100; // number of repetiton to avearge out the elapsed time .



int compare_matrices(float *gpu_mat, float *ref_mat)
{
	int result = 0;

	for(int j=0; j < N; j++)
    for(int i=0; i < N; i++)
    		if (ref_mat[i + j*N] != gpu_mat[i + j*N])
    		{
    			result = 1;
    		}
    return result;
}

/**
 * [make_matrix function fills the matrix with numbers from 0 to N-1]
 */

void  make_matrix(float * mat)
{
    for (int j=0; j<N*N; j++)
    {
        mat[j]=(float) j;
    }

}

/**
 * [prints matrix ]
 */

void print_matrix(float *mat)
{
	for(int j=0; j < N; j++)
	{
		for(int i=0; i < N; i++) { printf("%4.4g ", mat[i + j*N]); }
		printf("\n");
	}
}


/**
 * [transpose_CPU with row major order]
 *
 */

void
transpose_CPU(float in [ ], float out [ ] )
{
	for(int j=0; j < N; j++)
    for(int i=0; i < N; i++)
      		out [j + i*N] = in [i + j*N]; // reading and writing in row major order,  out(j,i) = in(i,j)
}

// ------------------------
 // Naive Transpose
// -------------------------

// Simple naive transpose which does not use shared memory.
// to be launched with one thread per element, in KxK threadblocks
// thread (x,y) in grid writes element (i,j) of output matrix
__global__ void
transpose_naive(float in[], float out[])
{
	int i = blockIdx.x * k + threadIdx.x;
	int j = blockIdx.y  * k + threadIdx.y;

	out[j + i*N] = in[i + j*N]; // reading is coaelsced but writing is uncoaelsced.
}


// ------------------------
 // transposeCoalesced
// -------------------------

// to be launched with one thread per element, in (tilesize)x(tilesize) threadblocks
// thread blocks read & write tiles, in coalesced fashion
// adjacent threads read adjacent input elements, write adjacent output elements
//Threads in  a thread block will copy the tile into shared memory and perform the transpose in the
//the shared memory which will be finally copied to global memory.

__global__ void
transpose_parallel_per_element_tiled(float in [],float out[])
{
    // (i,j) locations of the tile corner for input & output matrices:This shows where we start reading
    // from input and where to start writing in the output.

    int  in_corner_i= blockIdx.x * k,  in_corner_j=blockIdx.y * k; //which out(j,i) = in(i,j) block we are in mulltiplied by width of the tile.
    int out_corner_i=blockIdx.y * k,  out_corner_j = blockIdx.x * k; //output simply inverts y and x

    int x= threadIdx.x, y=threadIdx.y; //assigning x and y to thread index, tells which elemnt to read and write.

    __shared__  float tile[k][k]; //declare floating point array in shared memory for the tile

// coalesced read from global mem, TRANSPOSED write into shared mem:
tile [y][x] = in [(in_corner_i +x )+(in_corner_j+y)*N];// where tile starts + which element the particular thread is responsible for.

__syncthreads(); //threads wait here at the barrier

//read from shared mem,coalesced write to global mem:
out[(out_corner_i+x)+(out_corner_j+y)*N]=tile[x][y];//adjacent threads are varying by x

}


////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv)
{
    int numbytes= N*N* sizeof (float); // size of the matrix

   // allocate for input and output matrices
    float * in=(float*) malloc(numbytes);
    float * out=(float*)malloc (numbytes);
    float * gold_standard=(float*) malloc(numbytes);

   //calling the routine fill_matrix which inserts sequential numbers into the matrix.
    make_matrix(in);
    transpose_CPU(in, gold_standard); // transpose routine which puts result in  gold_standard for ref. comaprison.

   // allocate space for input and output matrix on device
    float *d_in,  *d_out ;

    cudaMalloc(&d_in, numbytes);
    cudaMalloc(&d_out, numbytes);
    cudaMemcpy(d_in,in,numbytes,cudaMemcpyHostToDevice); //copy matrix to the device
    GpuTimer timer;

	dim3 blocks(N/k,N/k); // blocks per grid
    dim3 threads(k,k); // threads per block


    timer.Start();
	 for (int i=0; i<repetiton;i++)
	 {
	         transpose_naive<<<blocks,threads>>>(d_in, d_out); //launching kernel running in single thread in single block.
      }
	timer.Stop();
	float avg_time=timer.Elapsed()/100;
    float bandwith= N*N*4*2*1e-6/avg_time;


	//copying the matrix from device to host
 	cudaMemcpy(out, d_out, numbytes, cudaMemcpyDeviceToHost);

 	printf("transpose_naive: %g ms.\nVerifying transpose...%s\n",
    avg_time, compare_matrices(out, gold_standard) ? "Unsuccessful" : "Successful");
    printf("Bandwidth: %g GB/s.\n",bandwith );
	printf(" *********************************** \n ");


    timer.Start();
	 for (int i=0; i<repetiton;i++)
	 {
	     transpose_parallel_per_element_tiled<<<blocks,threads>>>(d_in, d_out);
	 }
	timer.Stop();
	float avg_time2=timer.Elapsed()/100;
    float Bandwith= N*N*4*2*1e-6/avg_time2;

    cudaMemcpy(out, d_out, numbytes, cudaMemcpyDeviceToHost);

	printf("transpose_parallel_per_element_tiled %dx%d: %g ms.\nVerifying ...%s\n",
    k, k, avg_time2, compare_matrices(out, gold_standard) ? "Unsuccessful" : "Successful");
    printf("Bandwidth: %g GB/s.\n",Bandwith);


    cudaFree(d_in);
    cudaFree(d_out);
}
