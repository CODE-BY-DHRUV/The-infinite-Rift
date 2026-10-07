import java.util.*;

class Solution {
    public int maxFrequency(int[] arr, int k) {
        Arrays.sort(arr);

        long sum = 0;
        int left = 0;
        int ans = 1;

        for (int right = 0; right < arr.length; right++) {
            sum += arr[right];

            // Cost to make all elements in [left...right]
            // equal to arr[right]
            long cost = (long) arr[right] * (right - left + 1) - sum;

            // If cost exceeds k, shrink the window
            while (cost > k) {
                sum -= arr[left];
                left++;

                cost = (long) arr[right] * (right - left + 1) - sum;
            }

            ans = Math.max(ans, right - left + 1);
        }

        return ans;
    }
}