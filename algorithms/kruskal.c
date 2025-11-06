#include<stdio.h>
#include<stdlib.h>

#define MAX 100

int parent[MAX], rankArr[MAX];

typedef struct {
  int u, v, w;
} Edge;

void makeSet(int n) {
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    rankArr[i] = 0;
  }
}

int find(int x) {
  if (parent[x] != x)
    parent[x] = find(parent[x]);
  return parent[x];
}

void unionSet(int x, int y) {
  int xr = find(x);
  int yr = find(y);
  if (xr == yr) return;
  if (rankArr[xr] < rankArr[yr]) parent[xr] = yr;
  else if (rankArr[xr] > rankArr[yr]) parent[yr] = xr;
  else {
    parent[yr] = xr;
    rankArr[xr]++;
  }
}

int cmp(const void* a, const void* b) {
  return ((Edge*)a)->w - ((Edge*)b)->w;
}

void kruskal(Edge edges[], int n, int e) {
  makeSet(n);
  qsort(edges, e, sizeof(Edge), cmp);
  int total = 0;
  printf("Edges in MST:\n");
  for (int i = 0; i < e; i++) {
    int u = edges[i].u;
    int v = edges[i].v;
    int w = edges[i].w;
    if (find(u) != find(v)) {
      unionSet(u, v);
      total += w;
      printf("%d - %d : %d\n", u, v, w);
    }
  }
  printf("Total weight of MST: %d\n", total);
}

int main() {
  int n = 6, e = 9;
  Edge edges[] = {
    {0, 1, 4},
    {0, 2, 4},
    {1, 2, 2},
    {1, 0, 4},
    {2, 0, 4},
    {2, 1, 2},
    {2, 3, 3},
    {2, 5, 2},
    {2, 4, 4},
    {3, 4, 3},
    {4, 5, 3},
    {5, 3, 3}
  };
  kruskal(edges, n, 12);
  return 0;
}
