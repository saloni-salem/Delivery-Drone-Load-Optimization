
#include <stdio.h>
#include <time.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsackDP(int W, int wt[], int profit[], int n) {
    int i, w;
    int dp[n+1][W+1];

    for(i = 0; i <= n; i++) {
        for(w = 0; w <= W; w++) {
            if(i == 0 || w == 0)
                dp[i][w] = 0;
            else if(wt[i-1] <= w)
                dp[i][w] = max(profit[i-1] + dp[i-1][w-wt[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    return dp[n][W];
}

int knapsackGreedy(int W, int wt[], int profit[], int n) {
    float ratio[50];
    int i, j;

    for(i = 0; i < n; i++) {
        ratio[i] = (float)profit[i] / wt[i];
    }

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(ratio[i] < ratio[j]) {
                float r = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = r;

                int p = profit[i];
                profit[i] = profit[j];
                profit[j] = p;

                int w = wt[i];
                wt[i] = wt[j];
                wt[j] = w;
            }
        }
    }

    int totalProfit = 0;
    int totalWeight = 0;

    for(i = 0; i < n; i++) {
        if(totalWeight + wt[i] <= W) {
            totalWeight += wt[i];
            totalProfit += profit[i];
        }
    }

    return totalProfit;
}

int main() {
    int n, W, i;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int profit[n], wt[n];

    printf("Enter profits:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &profit[i]);
    }

    printf("Enter weights:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &wt[i]);
    }

    printf("Enter capacity: ");
    scanf("%d", &W);

    clock_t start, end;

    start = clock();
    int dpProfit = knapsackDP(W, wt, profit, n);
    end = clock();
    double dpTime = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    int greedyProfit = knapsackGreedy(W, wt, profit, n);
    end = clock();
    double greedyTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n--- Result Comparison ---\n");
    printf("DP Profit = %d\n", dpProfit);
    printf("Greedy Profit = %d\n", greedyProfit);

    printf("\n--- Time Comparison ---\n");
    printf("DP Time = %f sec\n", dpTime);
    printf("Greedy Time = %f sec\n", greedyTime);

    return 0;
}
