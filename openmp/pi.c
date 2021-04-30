#include "omp.h"
#include "stdio.h"
#define PAD 8
#define NUM_THREADS 1
/* #define NUM_THREADS 2 */
/* #define NUM_THREADS 4 */
/* #define NUM_THREADS 8 */
/* #define NUM_THREADS 16 */
/* #define NUM_THREADS 32 */
/* #define NUM_THREADS 64 */
/* #define NUM_THREADS 128 */

static long num_steps = 100000000;
double step;
int main(int argc, char **argv) {
  double pi = 0.0;
  step = 1.0 / (double)num_steps;
  double sum[NUM_THREADS][PAD];
  double tdata = omp_get_wtime();
  /* omp_set_dynamic(0); */
  omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
  {
    int i, id = omp_get_thread_num();
    double x;
    /* printf("Num threads: %d\n", omp_get_num_threads()); */
    for (i = id, sum[id][0] = 0.0; i < num_steps; i += omp_get_num_threads()) {
      x = (i + 0.5) * step;
      sum[id][0] += 4.0 / (1.0 + x * x);
      /* printf("Id: %d\n sum[id]: %f\n", id, sum[id]); */
    }
  }
  for (int i = 0; i < NUM_THREADS; i++)
    pi += sum[i][0] * step;
  tdata = omp_get_wtime() - tdata;
  printf("Pi: %f in %f seconds\n", pi, tdata);
  return 0;
}

/*
 * Has Quite poor scaling with threads
 * Overcome by using padding
 */
