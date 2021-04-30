#include "omp.h"
#include "stdio.h"

int main(int argc, char **argv) {
  /* omp_set_num_threads(4); */
#pragma omp parallel
  {
    printf("Hello");
    printf("world!\n");
  }
  return 0;
}
