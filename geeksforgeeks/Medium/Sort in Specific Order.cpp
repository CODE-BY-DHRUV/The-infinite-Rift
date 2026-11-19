
import java.util.*;

class Solution {
    public void sortIt(int[] arr) {

        Integer[] nums = new Integer[arr.length];

        for (int i = 0; i < arr.length; i++) {
            nums[i] = arr[i];
        }

        Arrays.sort(nums, (a, b) -> {

            boolean oddA = (a % 2 != 0);
            boolean oddB = (b % 2 != 0);

            if (oddA && oddB) {
                return Integer.compare(b, a);
            }

            if (!oddA && !oddB) {
                return Integer.compare(a, b);
            }

            return oddA ? -1 : 1;
        });

        for (int i = 0; i < arr.length; i++) {
            arr[i] = nums[i];
        }
    }
}
