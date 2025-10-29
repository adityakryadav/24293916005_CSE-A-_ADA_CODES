#include <stdio.h>

int fib_iterative(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n = 10;
    printf("Iterative Fibonacci(%d) = %d\n", n, fib_iterative(n));
    return 0;
}