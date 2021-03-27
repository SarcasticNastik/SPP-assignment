#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/* #define min(x, y) (y ^ ((x ^ y) & -(x < y))) */

unsigned int vertex, edges;
long int **adj;

long int min(long int x, long int y) {
  if (x < y)
    return x;
  return y;
}
void input() {
  long int x, y, w;
  for (int i = 0; i < edges; ++i) {
    scanf("%ld %ld %ld", &x, &y, &w);
    adj[--x][--y] = w;
  }
}

void set_memory() {
  adj = (long int **)malloc(vertex * sizeof(long int *));
  for (int i = 0; i < vertex; i++) {
    adj[i] = (long int *)malloc(vertex * sizeof(long int));
    memset(adj[i], 1000000, vertex * sizeof(long int));
  }
  /* printf("After allocating memory, array is:\n"); */
  /* for (int i = 0; i < vertex; i++) { */
  /*   for (int j = 0; j < vertex; ++j) */
  /*     printf("%u ", adj[i][j]); */
  /*   printf("\n"); */
  /* } */
}

void floyd_warshall() {
  for (int k = 0; k < vertex; ++k)
    for (int i = 0; i < vertex; ++i)
      for (int j = 0; j < vertex; ++j)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

void output() {
  for (int i = 0; i < vertex; ++i) {
    for (int j = 0; j < vertex; ++j) {
      if (adj[i][j] >= (long int)1000000)
        printf("-1 ");
      else
        printf("%ld ", adj[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {
  scanf("%u %u", &vertex, &edges);
  set_memory();
  input();
  floyd_warshall();
  output();
  return 0;
}
