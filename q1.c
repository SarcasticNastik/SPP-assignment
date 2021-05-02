#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <time.h>
#define BILLION 1000000000L
#define EXIT_FAILURE 1

typedef struct {
  long long int *arr;
  int x, y;
} Matrix;

int NUM_MATRIX = 0;

Matrix *product;
Matrix **matrices;
int order[5][5];

Matrix *matmul(Matrix *a, Matrix *b) {
  Matrix *prod = malloc(sizeof(Matrix));
  prod->x = a->x;
  prod->y = b->y;
  prod->arr = calloc(prod->x * prod->y, sizeof(long long int));
  int i, j, k;
  long long int *ptr, *saveptr, value;
#pragma omp parallel for shared(a, b, prod) private(i, k, j, value, saveptr,   \
                                                    ptr)
  for (i = 0; i < a->x; i++)
    for (k = 0; k < a->y; k++) {
      value = a->arr[i * a->y + k];
      saveptr = &prod->arr[i * prod->y];
      ptr = &b->arr[k * b->y];

      for (j = 0; j <= b->y - 16; j += 16) {
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
        *saveptr++ += value * *ptr++;
      }

      for (; j < b->y; ++j)
        *saveptr++ += value * *ptr++;
    }
  return prod;
}

Matrix *multiply_by_order(int i, int j, int k) {
  if (i == k)
    return matrices[i - 1];
  if (i == j && j + 1 == k)
    return matmul(matrices[i - 1], matrices[k - 1]);
  if (i == j)
    return matmul(matrices[i - 1],
                  multiply_by_order(j + 1, order[j][k - 1], k));
  if (j + 1 == k)
    return matmul(multiply_by_order(i, order[i - 1][j - 1], j),
                  matrices[k - 1]);

  return matmul(multiply_by_order(i, order[i - 1][j - 1], j),
                multiply_by_order(j + 1, order[j][k - 1], k));
}

void input_and_memory() {
  int i, j, k;
  scanf("%d", &NUM_MATRIX);
  matrices = (Matrix **)malloc(sizeof(Matrix *) * NUM_MATRIX);
  for (i = 0; i < NUM_MATRIX; ++i)
    matrices[i] = (Matrix *)malloc(sizeof(Matrix));
  int temp_x, temp_y;
  for (i = 0; i < NUM_MATRIX; ++i) {
    scanf("%d%d", &temp_x, &temp_y);
    matrices[i]->x = temp_x;
    matrices[i]->y = temp_y;
    matrices[i]->arr = malloc(temp_x * temp_y * sizeof(long long int));
    for (j = 0; j < temp_x; ++j)
      for (k = 0; k < temp_y; ++k) {
        scanf("%lld", &(matrices[i]->arr[j * temp_y + k]));
      }
  }
}

void logic() {
  int i, j, k, l, sum;

  int dp[NUM_MATRIX][NUM_MATRIX];
  for (i = 0; i < NUM_MATRIX; ++i)
    for (j = 0; j < NUM_MATRIX; ++j)
      dp[i][j] = order[i][j] = -1;

  for (i = 0; i < NUM_MATRIX; ++i) {
    for (j = 0; j < NUM_MATRIX; ++j) {
      k = i + j + 1;
      if (k <= NUM_MATRIX) {
        if (j + 1 == k)
          dp[j][k - 1] = 0;
        else {
          dp[j][k - 1] = -1;
          for (l = j + 1; l < k; l++) {
            sum = dp[j][l - 1] + dp[l][k - 1] +
                  matrices[j]->x * matrices[l - 1]->y * matrices[k - 1]->y;
            if (dp[j][k - 1] == -1) {
              dp[j][k - 1] = sum;
              order[j][k - 1] = l;
            } else if (dp[j][k - 1] > sum) {
              dp[j][k - 1] = sum;
              order[j][k - 1] = l;
            }
          }
        }
      }
    }
  }

  product = multiply_by_order(1, order[0][NUM_MATRIX - 1], NUM_MATRIX);
}

void output() {
  int i, j;
  printf("%d %d\n", product->x, product->y);
  for (i = 0; i < product->x; ++i) {
    for (j = 0; j < product->y; ++j)
      printf("%lld ", product->arr[i * product->x + j]);
    printf("\n");
  }
};

int main(int argc, char **argv) {

  input_and_memory();
  logic();
  output();

  return 0;
}
