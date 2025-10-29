#include <stdio.h>

// A utility function to return max of two integers
int max(int a, int b) {
return (a > b) ? a : b;
}

// Function to solve 0/1 Knapsack problem using Dynamic Programming
int knapSack(int W, int wt[], int val[], int n) {
int dp[n + 1][W + 1];

for (int i = 0; i <= n; i++) {
for (int w = 0; w <= W; w++) {
if (i == 0 || w == 0)
dp[i][w] = 0;
else if (wt[i - 1] <= w)
dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
else
dp[i][w] = dp[i - 1][w];
}
}
return dp[n][W];
}

int main() {
int n, W;
printf("Enter number of items: ");
scanf("%d", &n);

int val[n], wt[n];
printf("Enter value and weight of each item:\n");
for (int i = 0; i < n; i++) {
scanf("%d %d", &val[i], &wt[i]);
}

printf("Enter capacity of knapsack: ");
scanf("%d", &W);

int maxValue = knapSack(W, wt, val, n);
printf("Maximum value in Knapsack = %d\n", maxValue);

return 0;
}