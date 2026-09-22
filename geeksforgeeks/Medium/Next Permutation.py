class Solution {
    void nextPermutation(int[] arr) {
        int n = arr.length;

        // Step 1: Find the first index from the right
        // where arr[i] < arr[i + 1]
        int i = n - 2;

        while (i >= 0 && arr[i] >= arr[i + 1]) {
            i--;
        }

        // Step 2: If such an index exists,
        // find the smallest element greater than arr[i]
        if (i >= 0) {
            int j = n - 1;

            while (j >= 0 && arr[j] <= arr[i]) {
                j--;
            }

            // Swap pivot with successor
            swap(arr, i, j);
        }

        // Step 3: Reverse the suffix
        reverse(arr, i + 1, n - 1);
    }

    private void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    private void reverse(int[] arr, int left, int right) {
        while (left < right) {
            swap(arr, left, right);
            left++;
            right--;
        }
    }
}