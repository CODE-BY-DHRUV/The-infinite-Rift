class Solution {
    static final int MOD = 1_000_000_007;

    public int ways(int x, int y) {
        int[][] dp = new int[x + 1][y + 1];

        // Only left moves are possible
        for (int i = 0; i <= x; i++) {
            dp[i][0] = 1;
        }

        // Only down moves are possible
        for (int j = 0; j <= y; j++) {
            dp[0][j] = 1;
        }

        // DP
        for (int i = 1; i <= x; i++) {
            for (int j = 1; j <= y; j++) {
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
            }
        }

        return dp[x][y];
    }
}