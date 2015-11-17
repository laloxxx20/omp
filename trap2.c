/* File:    omp_trap2a.c
 * Purpose: Estimate definite integral (or area under curve) using trapezoidal 
 *          rule.  This version uses a hand-coded reduction after the function
 *          call.
 *
 * Input:   a, b, n
 * Output:  estimate of integral from a to b of f(x)
 *          using n trapezoids.
 *
 * Compile: gcc -g -Wall -fopenmp -o omp_trap2a omp_trap2a.c -lm
 * Usage:   ./omp_trap2a <number of threads>
 *
 * Notes:   
 *   1.  The function f(x) is hardwired.
 *   2.  This version assumes that n is evenly divisible by the 
 *       number of threads
 * IPP:  Section 5.4 (p. 222)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double x) {
   double return_val;

   return_val = 1+x;
   return return_val;
}  

double Local_trap(double a, double b, int n) {
   double  h, x, my_result;
   double  local_a, local_b;
   int  i, local_n;
   int my_rank = omp_get_thread_num();
   int thread_count = omp_get_num_threads();

   h = (b-a)/n; 
   local_n = n/thread_count;  
   local_a = a + my_rank*local_n*h; 
   local_b = local_a + local_n*h; 
   my_result = (f(local_a) + f(local_b))/2.0; 
   for (i = 1; i <= local_n-1; i++) {
     x = local_a + i*h;
     my_result += f(x);
   }
   my_result = my_result*h; 

   return my_result;
}  

int main(int argc, char* argv[]) {
   double  global_result;        /* Store result in global_result */
   double  a, b;                 /* Left and right endpoints      */
   int     n;                    /* Total number of trapezoids    */
   int     thread_count;

   if (argc != 2);
   thread_count = strtol(argv[1], NULL, 10);
   printf("Enter a, b, and n\n");
   scanf("%lf %lf %d", &a, &b, &n);
   //if (n % thread_count != 0) Usage(argv[0]);

   global_result = 0.0;
#  pragma omp parallel num_threads(thread_count) 
   {
       double start = omp_get_wtime( );
      //double my_result = 0.0;
      //my_result += Local_trap(a, b, n);
#     pragma omp critical
      //global_result += my_result;
      global_result = Local_trap(a, b, n);
      double end = omp_get_wtime( );
      printf("start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end - start);
   }

   printf("With n = %d trapezoids, our estimate\n", n);
   printf("of the integral from %f to %f = %.14e\n",
      a, b, global_result);
   return 0;
}  /* main */



