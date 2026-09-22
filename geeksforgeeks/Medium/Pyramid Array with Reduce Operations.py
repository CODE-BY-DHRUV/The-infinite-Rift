class Solution {
    public int formPyramid(int[] arr) {
        int n = arr.length;

        int[] left = new int[n];
        int[] right = new int[n];

        // Maximum possible height at i from the left
        left[0] = 1;
        for (int i = 1; i < n; i++) {
            left[i] = Math.min(arr[i], left[i - 1] + 1);
        }

        // Maximum possible height at i from the right
        right[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            right[i] = Math.min(arr[i], right[i + 1] + 1);
        }

        long total = 0;
        int maxPeak = 0;

        for (int i = 0; i < n; i++) {
            total += arr[i];

            int peak = Math.min(left[i], right[i]);
            maxPeak = Math.max(maxPeak, peak);
        }

        // Sum of a complete pyramid with peak x is x^2
        long pyramidSum = (long) maxPeak * maxPeak;

        return (int)(total - pyramidSum);
    }
}