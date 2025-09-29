#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2000

int rodCount;
int L[MAXN+1], P[MAXN+1];
int memo[MAXN+1][MAXN+1];
int dp[MAXN+1][MAXN+1];
long long callCounter = 0;

void buildPrefix() {
    P[0] = 0;
    for (int i = 1; i <= rodCount; ++i) P[i] = P[i-1] + L[i];
}

    int rec(int i, int j) {
    callCounter++;
    if (i == j) return 0;
    int bestCost = INT_MAX;
    int weld = P[j] - P[i-1];
    for (int k = i; k < j; ++k) {
    int left  = rec(i, k);
    int right = rec(k+1, j);
    int cost  = left + right + weld;
    if (cost < bestCost) bestCost = cost;
        }
     return bestCost;
    }

    int memoRec(int i, int j) {
    if (memo[i][j] != -1) return memo[i][j];
    if (i == j) return memo[i][j] = 0;
    int bestCost = INT_MAX;
    int weld = P[j] - P[i-1];
    for (int k = i; k < j; ++k) {
    int left  = memoRec(i, k);
    int right = memoRec(k+1, j);
    int cost  = left + right + weld;
    if (cost < bestCost) bestCost = cost;
    }
    return memo[i][j] = bestCost;
    }

   void bottomUp() {
    for (int i = 1; i <= rodCount; ++i) dp[i][i] = 0;
    for (int length = 2; length <= rodCount; ++length) {
        for (int i = 1; i+length-1 <= rodCount; ++i) {
            int j = i+length-1;
            int weld = P[j] - P[i-1], bestCost = INT_MAX;
            for (int k = i; k < j; ++k)
                bestCost = (dp[i][k] + dp[k+1][j] + weld < bestCost)
                     ? dp[i][k] + dp[k+1][j] + weld : bestCost;
            dp[i][j] = bestCost;
        }
    }
}

int main(int argc, char **argv) {
    char mode = argv[1][0];
    rodCount = atoi(argv[2]);
    for (int i = 1; i <= rodCount; ++i) L[i] = atoi(argv[2+i]);
    buildPrefix();
    for (int i = 1; i <= rodCount; ++i)
      for (int j = 1; j <= rodCount; ++j)
        memo[i][j] = -1;

        for (int i = 1; i <= rodCount; ++i)
          for (int j = 1; j <= rodCount; ++j)
            dp[i][j] = -1;

    switch(mode) {
      case 'R': printf("%d\n", rec(1,rodCount));
      break;
      case 'r': rec(1,rodCount); printf("%lld\n", callCounter);
      break;
      case 'M': printf("%d\n", memoRec(1,rodCount));
      break;
      case 'm':
        memoRec(1,rodCount);
        for (int i = 1; i <= rodCount; ++i) {
          for (int j = 1; j <= rodCount; ++j)
            printf("%d ", memo[i][j]);
          printf("\n");
        }
        break;
      case 'D':
        bottomUp();
        printf("%d\n", dp[1][rodCount]);
        break;
      case 'd':
        bottomUp();
        for (int i = 1; i <= rodCount; ++i) {
          for (int j = 1; j <= rodCount; ++j)
            printf("%d ", dp[i][j]);
          printf("\n");
        }
        break;
    }
    return 0;
}
