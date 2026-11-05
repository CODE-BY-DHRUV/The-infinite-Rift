
class Solution {
    static final long MOD = 1000000007L;

    static long countBT(int h) {

        if (h == 0 || h == 1) {
            return 1;
        }

        long prev2 = 1; // dp[0]
        long prev1 = 1; // dp[1]

        for (int i = 2; i <= h; i++) {

            long current = (
                (prev1 * prev1) % MOD
                + (2 * prev1 % MOD * prev2) % MOD
            ) % MOD;

            prev2 = prev1;
            prev1 = current;
        }

        return prev1;
    }
}
