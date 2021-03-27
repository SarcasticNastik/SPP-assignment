#include "stdio.h"

int NUM_MATRIX = 0;
int *dimensions;
int **product;
int ***matrices;

struct Matrix {
  int **matrix;
  int x, y;
};

int main(int argc, char **argv) {
  /**
   * Input
   */
  /* printf("\nPlease enter the number of matrices: "); */
  scanf("%d", &NUM_MATRIX);

  matrices = malloc(NUM_MATRIX * sizeof(int **));
  dimensions = malloc(NUM_MATRIX * 2 * sizeof(int));
  for (int i = 0; i < NUM_MATRIX; ++i) {
    int x_k, y_k;
    /* printf("\nPlease enter (r_%d, c_%d): ", i, i); */
    scanf("%d %d", &x_k, &y_k);
    dimensions[2 * i] = x_k;
    dimensions[2 * i + 1] = y_k;
    matrices[i] = malloc(x_k * sizeof(int *));
    for (int j = 0; j < x_k; ++j) {
      matrices[i][j] = malloc(y_k * sizeof(int));
      for (int k = 0; k < y_k; ++k) {
        scanf("%d", &matrices[i][j][k]);
      }
    }
  }

  product = (int **)malloc(dimensions[0] * sizeof(int *));
  for (int i = 0; i < dimensions[0]; i++)
    product[i] = (int *)malloc(dimensions[2 * NUM_MATRIX - 1] * sizeof(int));

  // Here, check if:
  // 1. having a temporary buffer matrix declared once is faster; or
  // 2. creating a smaller array declared at each step
  for (int i = 0; i < NUM_MATRIX - 1; i++) {
    int **a = (int **)malloc(dimensions[0] * sizeof(int *));
    for (int j = 0; j < dimensions[0]; j++)
      a[j] = (int *)malloc(dimensions[2 * i] * sizeof(int));
  }

  /**
   * Output
   */
  for (int i = 0; i < dimensions[0]; i++) {
    for (int j = 0; j < dimensions[2 * NUM_MATRIX - 1]; j++)
      printf("%d ", product[i][j]);
    printf("\n");
  }
  return 0;
}
