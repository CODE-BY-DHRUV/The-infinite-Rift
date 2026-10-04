import java.util.*;

class Solution {
    public ArrayList<ArrayList<Integer>> socialNetwork(int[] arr) {
        int n = arr.length + 1;
        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();

        for (int i = 2; i <= n; i++) {
            int[] dist = new int[n + 1];

            int cur = i;
            int steps = 0;

            // Follow the friend chain
            while (cur != 1) {
                cur = arr[cur - 2];
                steps++;
                dist[cur] = steps;
            }

            // j must be in increasing order
            for (int j = 1; j < i; j++) {
                if (dist[j] > 0) {
                    ArrayList<Integer> temp = new ArrayList<>();
                    temp.add(i);
                    temp.add(j);
                    temp.add(dist[j]);
                    ans.add(temp);
                }
            }
        }

        return ans;
    }
}