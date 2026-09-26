import java.util.*;

class Solution {
    public int minXor(int[] arr) {
        Arrays.sort(arr);

        int ans = Integer.MAX_VALUE;

        for (int i = 1; i < arr.length; i++) {
            ans = Math.min(ans, arr[i] ^ arr[i - 1]);
        }

        return ans;
    }
}