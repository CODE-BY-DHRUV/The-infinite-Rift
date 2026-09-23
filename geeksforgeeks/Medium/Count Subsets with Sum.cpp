
class Solution {

    public int perfectSum(int[] arr, int target) {

        int[] dp = new int[target + 1];

        // Empty subset
        dp[0] = 1;

        for (int x : arr) {

            // Traverse backwards so each element is used only once
            for (int sum = target; sum >= x; sum--) {
                dp[sum] += dp[sum - x];
            }
        }

        return dp[target];
    }
}

