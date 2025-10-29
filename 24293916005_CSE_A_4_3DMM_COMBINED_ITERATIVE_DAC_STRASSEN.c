#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** allocateMatrix(int n) {
    int **mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        mat[i] = (int*)malloc(n * sizeof(int));
    return mat;
}
void freeMatrix(int **mat, int n) {
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}
void fillRandom(int **mat, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 10;
}

void multiplyIterative(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void add(int **A, int **B, int **C, int n) {
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            C[i][j] = A[i][j] + B[i][j];
}
void sub(int **A, int **B, int **C, int n) {
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void multiplyDAC(int **A, int **B, int **C, int n) {
    if (n == 1) { C[0][0] = A[0][0] * B[0][0]; return; }
    int k = n/2;
    int **a11=allocateMatrix(k),**a12=allocateMatrix(k),
        **a21=allocateMatrix(k),**a22=allocateMatrix(k),
        **b11=allocateMatrix(k),**b12=allocateMatrix(k),
        **b21=allocateMatrix(k),**b22=allocateMatrix(k),
        **c11=allocateMatrix(k),**c12=allocateMatrix(k),
        **c21=allocateMatrix(k),**c22=allocateMatrix(k),
        **t1=allocateMatrix(k),**t2=allocateMatrix(k);

    for (int i=0;i<k;i++)
        for (int j=0;j<k;j++){
            a11[i][j]=A[i][j]; a12[i][j]=A[i][j+k];
            a21[i][j]=A[i+k][j]; a22[i][j]=A[i+k][j+k];
            b11[i][j]=B[i][j]; b12[i][j]=B[i][j+k];
            b21[i][j]=B[i+k][j]; b22[i][j]=B[i+k][j+k];
        }

    multiplyDAC(a11,b11,t1,k); multiplyDAC(a12,b21,t2,k); add(t1,t2,c11,k);
    multiplyDAC(a11,b12,t1,k); multiplyDAC(a12,b22,t2,k); add(t1,t2,c12,k);
    multiplyDAC(a21,b11,t1,k); multiplyDAC(a22,b21,t2,k); add(t1,t2,c21,k);
    multiplyDAC(a21,b12,t1,k); multiplyDAC(a22,b22,t2,k); add(t1,t2,c22,k);

    for (int i=0;i<k;i++)
        for (int j=0;j<k;j++){
            C[i][j]=c11[i][j]; C[i][j+k]=c12[i][j];
            C[i+k][j]=c21[i][j]; C[i+k][j+k]=c22[i][j];
        }

    freeMatrix(a11,k);freeMatrix(a12,k);freeMatrix(a21,k);freeMatrix(a22,k);
    freeMatrix(b11,k);freeMatrix(b12,k);freeMatrix(b21,k);freeMatrix(b22,k);
    freeMatrix(c11,k);freeMatrix(c12,k);freeMatrix(c21,k);freeMatrix(c22,k);
    freeMatrix(t1,k);freeMatrix(t2,k);
}

void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) { C[0][0] = A[0][0] * B[0][0]; return; }
    int k=n/2;
    int **a11=allocateMatrix(k),**a12=allocateMatrix(k),
        **a21=allocateMatrix(k),**a22=allocateMatrix(k),
        **b11=allocateMatrix(k),**b12=allocateMatrix(k),
        **b21=allocateMatrix(k),**b22=allocateMatrix(k),
        **m1=allocateMatrix(k),**m2=allocateMatrix(k),**m3=allocateMatrix(k),
        **m4=allocateMatrix(k),**m5=allocateMatrix(k),**m6=allocateMatrix(k),
        **m7=allocateMatrix(k),**t1=allocateMatrix(k),**t2=allocateMatrix(k),
        **c11=allocateMatrix(k),**c12=allocateMatrix(k),
        **c21=allocateMatrix(k),**c22=allocateMatrix(k);

    for (int i=0;i<k;i++)
        for (int j=0;j<k;j++){
            a11[i][j]=A[i][j]; a12[i][j]=A[i][j+k];
            a21[i][j]=A[i+k][j]; a22[i][j]=A[i+k][j+k];
            b11[i][j]=B[i][j]; b12[i][j]=B[i][j+k];
            b21[i][j]=B[i+k][j]; b22[i][j]=B[i+k][j+k];
        }

    add(a11,a22,t1,k); add(b11,b22,t2,k); strassen(t1,t2,m1,k);
    add(a21,a22,t1,k); strassen(t1,b11,m2,k);
    sub(b12,b22,t2,k); strassen(a11,t2,m3,k);
    sub(b21,b11,t2,k); strassen(a22,t2,m4,k);
    add(a11,a12,t1,k); strassen(t1,b22,m5,k);
    sub(a21,a11,t1,k); add(b11,b12,t2,k); strassen(t1,t2,m6,k);
    sub(a12,a22,t1,k); add(b21,b22,t2,k); strassen(t1,t2,m7,k);

    add(m1,m4,t1,k); sub(t1,m5,t2,k); add(t2,m7,c11,k);
    add(m3,m5,c12,k); add(m2,m4,c21,k);
    sub(m1,m2,t1,k); add(t1,m3,t2,k); add(t2,m6,c22,k);

    for (int i=0;i<k;i++)
        for (int j=0;j<k;j++){
            C[i][j]=c11[i][j]; C[i][j+k]=c12[i][j];
            C[i+k][j]=c21[i][j]; C[i+k][j+k]=c22[i][j];
        }

    freeMatrix(a11,k);freeMatrix(a12,k);freeMatrix(a21,k);freeMatrix(a22,k);
    freeMatrix(b11,k);freeMatrix(b12,k);freeMatrix(b21,k);freeMatrix(b22,k);
    freeMatrix(m1,k);freeMatrix(m2,k);freeMatrix(m3,k);freeMatrix(m4,k);
    freeMatrix(m5,k);freeMatrix(m6,k);freeMatrix(m7,k);
    freeMatrix(t1,k);freeMatrix(t2,k);
    freeMatrix(c11,k);freeMatrix(c12,k);freeMatrix(c21,k);freeMatrix(c22,k);
}

int main() {
    srand(time(NULL));
    int sizes[] = {2,4,8,16,32,64};
    for (int s=0;s<6;s++) {
        int n=sizes[s];
        int **A=allocateMatrix(n),**B=allocateMatrix(n),**C=allocateMatrix(n);
        fillRandom(A,n); fillRandom(B,n);

        clock_t start,end;
        printf("\nSize %d x %d\n",n,n);

        start=clock(); multiplyIterative(A,B,C,n); end=clock();
        printf("Iterative: %.3f sec\n",(double)(end-start)/CLOCKS_PER_SEC);

        start=clock(); multiplyDAC(A,B,C,n); end=clock();
        printf("Divide&Conquer: %.3f sec\n",(double)(end-start)/CLOCKS_PER_SEC);

        start=clock(); strassen(A,B,C,n); end=clock();
        printf("Strassen: %.3f sec\n",(double)(end-start)/CLOCKS_PER_SEC);

        freeMatrix(A,n); freeMatrix(B,n); freeMatrix(C,n);
    }
    return 0;
}