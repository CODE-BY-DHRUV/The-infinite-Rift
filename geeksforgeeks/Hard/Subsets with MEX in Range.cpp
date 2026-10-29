class Solution {
    static final long MOD = 1_000_000_007L;

    public int cntSubsets(int[] arr, int l, int r) {
        int n = arr.length;
        int[] freq = new int[n + 1];

        for (int x : arr) {
            freq[x]++;
        }

        long[] pow2 = new long[n + 1];
        pow2[0] = 1;

        for (int i = 1; i <= n; i++) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        long[] suffix = new long[n + 2];

        for (int i = n; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + freq[i];
        }

        long ans = 0;
        long prefix = 1;

        for (int mex = 0; mex <= r; mex++) {
            if (mex > 0) {
                prefix = (prefix * (pow2[freq[mex - 1]] - 1 + MOD))
                         % MOD;
            }

            if (mex >= l) {
                long otherChoices = pow2[(int) suffix[mex + 1]];
                long ways = (prefix * otherChoices) % MOD;
                ans = (ans + ways) % MOD;
            }
        }

        return (int) ans;
    }
}