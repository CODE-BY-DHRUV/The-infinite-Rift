
import java.util.Arrays;

class Solution {
    public int findKthSmall(int[] arr, int k) {

        Arrays.sort(arr);

        int missing = 0;
        int prev = 0;

        for (int num : arr) {

            int gap = num - prev - 1;

            if (missing + gap >= k) {
                return prev + (k - missing);
            }

            missing += gap;
            prev = num;
        }

        return prev + (k - missing);
    }
}
