import java.util.*;

class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        while (T-- > 0) {
            int n = sc.nextInt();
            long k = sc.nextLong();

            HashMap<Integer, Integer> map = new HashMap<>();

            for (int i = 0; i < n; i++) {
                int x = sc.nextInt();
                map.put(x, map.getOrDefault(x, 0) + 1);
            }

            // Total number of pairs
            long totalPairs = (long) n * (n - 1) / 2;

            // Equal pairs
            long equalPairs = 0;

            ArrayList<Integer> improvements = new ArrayList<>();

            for (int freq : map.values()) {
                equalPairs += (long) freq * (freq - 1) / 2;

                // If we change elements of this group:
                // improvements are freq-1, freq-2, ..., 1
                for (int j = 1; j < freq; j++) {
                    improvements.add(j);
                }
            }

            // Take the biggest improvements first
            Collections.sort(improvements, Collections.reverseOrder());

            long removed = 0;

            int operations = (int) Math.min(k, improvements.size());

            for (int i = 0; i < operations; i++) {
                removed += improvements.get(i);
            }

            long answer = totalPairs - equalPairs + removed;

            System.out.println(answer);
        }
    }
}