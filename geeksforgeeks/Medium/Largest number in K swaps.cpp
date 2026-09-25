class Solution {

    String ans;

    // Function to find the largest number after k swaps.
    public String findMaximumNum(String s, int k) {
        ans = s;

        char[] arr = s.toCharArray();
        solve(arr, k, 0);

        return ans;
    }

    void solve(char[] arr, int k, int index) {

        if (k == 0 || index == arr.length) {
            String current = new String(arr);

            if (current.compareTo(ans) > 0) {
                ans = current;
            }

            return;
        }

        // Find the maximum digit from index onwards
        char maxDigit = arr[index];

        for (int i = index + 1; i < arr.length; i++) {
            if (arr[i] > maxDigit) {
                maxDigit = arr[i];
            }
        }

        // If current digit is already maximum,
        // move to the next position without using a swap.
        if (arr[index] == maxDigit) {
            solve(arr, k, index + 1);
            return;
        }

        // Try swapping with every occurrence of maxDigit
        for (int i = index + 1; i < arr.length; i++) {

            if (arr[i] == maxDigit) {

                // Swap
                char temp = arr[index];
                arr[index] = arr[i];
                arr[i] = temp;

                // Update answer
                String current = new String(arr);
                if (current.compareTo(ans) > 0) {
                    ans = current;
                }

                // Use one swap
                solve(arr, k - 1, index + 1);

                // Backtrack
                temp = arr[index];
                arr[index] = arr[i];
                arr[i] = temp;
            }
        }
    }
}