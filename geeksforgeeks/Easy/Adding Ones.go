
import java.util.*;

class Solution {
    public ArrayList<Integer> update(int n, int[] updates) {
        int[] freq = new int[n];

        for (int j : updates) {
            freq[j - 1]++;
        }

        ArrayList<Integer> arr = new ArrayList<>();
        int count = 0;

        for (int i = 0; i < n; i++) {
            count += freq[i];
            arr.add(count);
        }

        return arr;
    }
}
