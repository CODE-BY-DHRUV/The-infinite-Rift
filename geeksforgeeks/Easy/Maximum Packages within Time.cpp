class Solution {
    public int maxPackages(int[] arr, int totalTime) {
        int n = arr.length;
        // The maximum window size is bounded by the array length
        int k = Math.min(n, totalTime);

        // Compute sum of the first window of size k
        int currentSum = 0;
        for (int i = 0; i < k; i++) {
            currentSum += arr[i];
        }

        int maxSum = currentSum;

        // Slide the window across the array
        for (int i = k; i < n; i++) {
            currentSum += arr[i] - arr[i - k];
            maxSum = Math.max(maxSum, currentSum);
        }

        return maxSum;
    }
}