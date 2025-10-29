#include <stdio.h>

int memo[1000];

int fib_memo(int n) {
    if (memo[n] != -1) return memo[n];
    if (n == 0) return memo[n] = 0;
    if (n == 1) return memo[n] = 1;
    return memo[n] = fib_memo(n-1) + fib_memo(n-2);
}

int main() {
    int n = 10;
    for (int i = 0; i <= n; i++) memo[i] = -1;
    printf("Top-Down DP Fibonacci(%d) = %d\n", n, fib_memo(n));
    return 0;
}