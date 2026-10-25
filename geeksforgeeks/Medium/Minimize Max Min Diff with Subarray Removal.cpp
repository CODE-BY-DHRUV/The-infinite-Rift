import java.util.*;

class Solution {
    public int minDiff(int k, int[] arr) {
        int n = arr.length;

        // If removing k elements leaves 0 or 1 element remaining
        if (n - k <= 1) return 0;

        // Precompute prefix max and min
        int[] prefMax = new int[n];
        int[] prefMin = new int[n];
        prefMax[0] = prefMin[0] = arr[0];
        for (int i = 1; i < n; i++) {
            prefMax[i] = Math.max(prefMax[i - 1], arr[i]);
            prefMin[i] = Math.min(prefMin[i - 1], arr[i]);
        }

        // Precompute suffix max and min
        int[] suffMax = new int[n];
        int[] suffMin = new int[n];
        suffMax[n - 1] = suffMin[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffMax[i] = Math.max(suffMax[i + 1], arr[i]);
            suffMin[i] = Math.min(suffMin[i + 1], arr[i]);
        }

        int minDiff = Integer.MAX_VALUE;

        // Iterate over all possible subarray removal windows of length k
        for (int i = 0; i <= n - k; i++) {
            int maxVal = Integer.MIN_VALUE;
            int minVal = Integer.MAX_VALUE;

            // If prefix elements exist (i > 0)
            if (i > 0) {
                maxVal = Math.max(maxVal, prefMax[i - 1]);
                minVal = Math.min(minVal, prefMin[i - 1]);
            }

            // If suffix elements exist (i + k < n)
            if (i + k < n) {
                maxVal = Math.max(maxVal, suffMax[i + k]);
                minVal = Math.min(minVal, suffMin[i + k]);
            }

            minDiff = Math.min(minDiff, maxVal - minVal);
        }

        return minDiff;
    }
}