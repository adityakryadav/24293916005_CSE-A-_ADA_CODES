#include <stdio.h>

int fib_bottomup(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int dp[n+1];
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

int main() {
    int n = 10;
    printf("Bottom-Up DP Fibonacci(%d) = %d\n", n, fib_bottomup(n));
    return 0;
}