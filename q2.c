#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BILLION 1000000000L
#define EXIT_FAILURE 1

unsigned int vertex, edges;
int *adj;
int i, j, k, x, y, w;

void input() {
  for (i = 0; i < edges; ++i) {
    scanf("%d %d %d", &x, &y, &w);
    if (w < adj[(--x) * vertex + (--y)])
      adj[x * vertex + y] = w;
  }
}

void set_memory() {
  adj = malloc(sizeof(int) * (vertex * vertex));
  for (i = 0; i < vertex; ++i) {
    for (j = 0; j < vertex; ++j) {
      int temp = i * vertex + j;
      if (i == j)
        adj[temp] = 0;
      else
        adj[temp] = 1000001;
    }
  }
}

void floyd_warshall() {
  register int *ptr, *saveptr, ele1, ele2;
  for (k = 0; k < vertex; ++k) {
    for (i = 0; i < vertex; ++i) {
      ele1 = adj[i * vertex + k];
      if (ele1 >= 100000)
        continue;
      ptr = &adj[k * vertex];
      saveptr = &adj[i * vertex];
      for (j = 0; j <= vertex - 16; j += 16) {
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
        ele2 = ele1 + *ptr;
        if (ele2 < *saveptr)
          *saveptr = ele2;
        saveptr++, ptr++;
      }
      for (; j < vertex; j++) {
        if (ele1 + *ptr < *saveptr)
          *saveptr = ele1 + *ptr;
        saveptr++, ptr++;
      }
    }
  }
}

void output() {
  for (i = 0; i < vertex; ++i) {
    for (j = i * vertex; j < (i + 1) * vertex; ++j) {
      if (adj[j] >= 100000)
        printf("-1 ");
      else
        printf("%d ", adj[j]);
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {
  scanf("%u %u", &vertex, &edges);

  struct timespec begin, end;
  if (clock_gettime(CLOCK_REALTIME, &begin) == -1) {
    perror("clock gettime");
    return EXIT_FAILURE;
  }

  set_memory();
  input();
  floyd_warshall();

  if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
    perror("clock gettime");
    return EXIT_FAILURE;
  }
  double S = (end.tv_sec - begin.tv_sec);
  double NS = (double)(end.tv_nsec - begin.tv_nsec) / (double)BILLION;
  printf("%lf", S + NS);

  return 0;
}
