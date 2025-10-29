#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 64   // maximum matrix size

void addMatrix(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void multiplyRecursive(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n/2;
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];
    int M1[k][k], M2[k][k];

    // Divide matrices into submatrices
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }

    // Recursive multiplication (Divide & Conquer = 8 multiplications)
    multiplyRecursive(k, A11, B11, C11);
    multiplyRecursive(k, A12, B21, M1);
    addMatrix(k, C11, M1, C11);

    multiplyRecursive(k, A11, B12, C12);
    multiplyRecursive(k, A12, B22, M1);
    addMatrix(k, C12, M1, C12);

    multiplyRecursive(k, A21, B11, C21);
    multiplyRecursive(k, A22, B21, M1);
    addMatrix(k, C21, M1, C21);

    multiplyRecursive(k, A21, B12, C22);
    multiplyRecursive(k, A22, B22, M1);
    addMatrix(k, C22, M1, C22);

    // Combine into result C
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j+k] = C12[i][j];
            C[i+k][j] = C21[i][j];
            C[i+k][j+k] = C22[i][j];
        }
}

int main() {
    int n;
    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    // Initialize matrices
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }

    clock_t start = clock();
    multiplyRecursive(n, A, B, C);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Recursive (Divide & Conquer) multiplication completed in %f seconds\n", time_taken);

    return 0;
}
