#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main() {
    int n, key, index;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    key = n; // Worst case

    start = clock();
    index = binarySearch(arr, n, key);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (index != -1)
        printf("Element found at index %d\n", index);
    else
        printf("Element not found\n");

    printf("Time taken: %f seconds\n", cpu_time_used);

    free(arr);
    return 0;
}