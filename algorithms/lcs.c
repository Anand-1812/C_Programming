#include<stdio.h>
#include<string.h>

int dp[1001][1001];

int lcs(char X[], char Y[], int m, int n) {
  if (m == 0 || n == 0)
    return 0;
  if (dp[m][n] != -1)
    return dp[m][n];

  if (X[m - 1] == Y[n - 1])
    dp[m][n] = 1 + lcs(X, Y, m - 1, n - 1);
  else
    dp[m][n] = (lcs(X, Y, m - 1, n) > lcs(X, Y, m, n - 1))
      ? lcs(X, Y, m - 1, n)
      : lcs(X, Y, m, n - 1);

  return dp[m][n];
}

int main() {
  char X[] = "AGGTAB";
  char Y[] = "GXTXAYB";

  int m = strlen(X);
  int n = strlen(Y);

  for (int i = 0; i <= m; i++)
    for (int j = 0; j <= n; j++)
      dp[i][j] = -1;

  printf("Length of LCS is %d\n", lcs(X, Y, m, n));
  return 0;
}
