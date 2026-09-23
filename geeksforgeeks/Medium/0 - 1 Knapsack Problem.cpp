
class Solution {

    static int knapsack(int W, int val[], int wt[]) {

        int[] dp = new int[W + 1];

        for (int i = 0; i < val.length; i++) {

            for (int capacity = W; capacity >= wt[i]; capacity--) {

                dp[capacity] = Math.max(
                    dp[capacity],
                    val[i] + dp[capacity - wt[i]]
                );
            }
        }

        return dp[W];
    }
}

