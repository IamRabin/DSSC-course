
 #include<stdio.h>
 #include <omp.h>
 long steps_number=100000000;
 double step_size;

 void main()
 {
  double pic;
  int nthreads;//so that number of threads is visible outside the parallel region.
  step_size=1.0/(double)steps_number;

  /* ================================================
  *
  *  Using Critical Clause
  *==================================================
  */
  double tstart_c=omp_get_wtime();
  #pragma omp parallel
   {
       int j,idc,nthrds_c; double xc,sumc;//sumc is local to each thread to accumulate partial sum.
       idc = omp_get_thread_num();// Master thread id =0,saves the copy of number of threads given. After leaving the parallel region ,it is important
       nthrds_c = omp_get_num_threads();  //to know how many threads was allocated so we have assigned
       if (idc == 0) nthreads = nthrds_c;  //nthrds to nthreads which is shared.
       int steps_per_thread_c=steps_number/nthrds_c;
       int start_c=idc*steps_per_thread_c;
       int end_c=start_c+steps_per_thread_c;

       for (j=start_c;j< end_c;j++){
                  xc = (j+0.5)*step_size;
                  sumc += 4.0/(1.0+xc*xc);
        }
/*Critical clause helps in synchronization and impose order constraints
* which protects access to share data.The idea is only one thread at a time
* can enter the critial region.
*/
   #pragma omp critical
       pic += sumc*step_size;

  }

  double duration_c =omp_get_wtime()-tstart_c;
  printf("Critical Clause Run Time:%4.2f\n",duration_c);
  printf("Pi:%4.2f\n",pic);




   /* ===================================================
   *
   *  Using Atomic Clause
   *======================================================
   */

double pia = 0.0;

double tstart_a=omp_get_wtime();

//parallel region starts here
#pragma omp parallel
 {
     int k,ida,nthrds_a; double xa,suma;
      ida = omp_get_thread_num();
      nthrds_a = omp_get_num_threads();
     if (ida == 0) nthreads = nthrds_a;
     int steps_per_thread_a=steps_number/nthrds_a;
     int start_a=ida*steps_per_thread_a;
     int end_a=start_a+steps_per_thread_a;
     for (k=start_a;k< end_a;k++){
                xa = (k+0.5)*step_size;
                suma += 4.0/(1.0+xa*xa);
      }
      suma=suma*step_size;

/*Atomic also provides synchronisation but provides mutual exclusion only when
* memory location is updates as below.So threads take turn to update pia,so it
* only protects the read/update of pia.
*/
    #pragma atomic
       pia += suma ;


   }
   double duration_a =omp_get_wtime()-tstart_a;
   printf("Atomic Clause Run Time:%4.2f\n",duration_a);
   printf("Pi:%4.2f\n",pia);






/* ==================================================
*
*  Using Reduction Clause
*====================================================
*/

  int i; double xr,pir,sumr=0.0;
  step_size=1.0/(double)steps_number;

  double tstart_r=omp_get_wtime();

  #pragma omp parallel
   {
       int idr = omp_get_thread_num();
       int nthrds_r = omp_get_num_threads();
       if (idr == 0) nthreads = nthrds_r;
       int steps_per_thread_r=steps_number/nthrds_r;
       int start_r=idr*steps_per_thread_r;
       int end_r=start_r+steps_per_thread_r;


        #pragma omp for reduction(+:sumr)
             for (i=start_r;i< end_r;i++){
                      xr=(i+0.5)*step_size;
                      sumr+=4.0/(1.0+xr*xr);
                     }
     }
        pir=step_size*sumr;

  double duration_r =omp_get_wtime()-tstart_r;
  printf("Reduction Clause Run Time:%4.2f\n",duration_r);
  printf("Pi:%4.2f\n",pir);


/* ==================================================
*
* Serial code for Pi estimation
*====================================================
*/
int l; double a,pis,sum_s=0.0;
double tstart_s=omp_get_wtime();
for (l=0;l<steps_number;l++)
    {
          a=(l+0.5)*step_size;
          sum_s+=4.0/(1.0+a*a);
     }
      pis=step_size*sum_s;

 double duration_s =omp_get_wtime()-tstart_s;
 printf("Serial Code Run Time:%4.2f\n",duration_s);
 printf("Pi:%4.2f\n",pis);

}
