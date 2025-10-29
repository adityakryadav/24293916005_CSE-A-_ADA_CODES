#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 64

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

void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n/2;
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];
    int M1[k][k], M2[k][k], M3[k][k], M4[k][k], M5[k][k], M6[k][k], M7[k][k];
    int T1[k][k], T2[k][k];

    // Divide matrices
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

    // Strassen’s 7 multiplications
    addMatrix(k, A11, A22, T1); addMatrix(k, B11, B22, T2); strassen(k, T1, T2, M1);
    addMatrix(k, A21, A22, T1); strassen(k, T1, B11, M2);
    subMatrix(k, B12, B22, T1); strassen(k, A11, T1, M3);
    subMatrix(k, B21, B11, T1); strassen(k, A22, T1, M4);
    addMatrix(k, A11, A12, T1); strassen(k, T1, B22, M5);
    subMatrix(k, A21, A11, T1); addMatrix(k, B11, B12, T2); strassen(k, T1, T2, M6);
    subMatrix(k, A12, A22, T1); addMatrix(k, B21, B22, T2); strassen(k, T1, T2, M7);

    // Compute C quadrants
    addMatrix(k, M1, M4, T1); subMatrix(k, T1, M5, T2); addMatrix(k, T2, M7, C11);
    addMatrix(k, M3, M5, C12);
    addMatrix(k, M2, M4, C21);
    subMatrix(k, M1, M2, T1); addMatrix(k, T1, M3, T2); addMatrix(k, T2, M6, C22);

    // Combine into final matrix
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

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }

    clock_t start = clock();
    strassen(n, A, B, C);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Strassen multiplication completed in %f seconds\n", time_taken);

    return 0;
}
