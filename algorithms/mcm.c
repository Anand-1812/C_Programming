#include<stdio.h>
#include<limits.h>

int dp[100][100];

int matrixChain(int arr[], int i, int j) {
  if (i == j)
    return 0;
  if (dp[i][j] != -1)
    return dp[i][j];

  dp[i][j] = INT_MAX;
  for (int k = i; k < j; k++) {
    int cost = matrixChain(arr, i, k) + matrixChain(arr, k + 1, j) + arr[i - 1] * arr[k] * arr[j];
    if (cost < dp[i][j])
      dp[i][j] = cost;
  }
  return dp[i][j];
}

int main() {
  int arr[] = {10, 20 ,30, 40};
  int n = sizeof(arr) / sizeof(arr[0]);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      dp[i][j] = -1;

  printf("Minimum number of multiplications is %d\n", matrixChain(arr, 1, n - 1));
  return 0;
}
