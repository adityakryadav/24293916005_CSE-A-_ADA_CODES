#include <stdio.h>

int fib_recursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib_recursive(n-1) + fib_recursive(n-2);
}

int main() {
    int n = 10;
    printf("Recursive Fibonacci(%d) = %d\n", n, fib_recursive(n));
    return 0;
}