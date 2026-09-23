
class Solution {

    static Boolean isSubsetSum(int arr[], int sum) {

        boolean[] dp = new boolean[sum + 1];

        // Empty subset gives sum 0
        dp[0] = true;

        for (int x : arr) {

            // Go backwards so each element is used only once
            for (int s = sum; s >= x; s--) {

                if (dp[s - x]) {
                    dp[s] = true;
                }
            }
        }

        return dp[sum];
    }
}

