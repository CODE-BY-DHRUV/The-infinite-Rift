
import java.util.*;

class Solution {

    public ArrayList<Integer> findPairs(int[] arr) {

        int n = arr.length;

        HashMap<Long, ArrayList<Integer>> map = new HashMap<>();

        // Generate all pairs in lexicographical order
        for (int a = 0; a < n; a++) {
            for (int b = a + 1; b < n; b++) {

                long sum = (long) arr[a] + arr[b];

                int encoded = a * n + b;

                map.computeIfAbsent(sum, k -> new ArrayList<>())
                   .add(encoded);
            }
        }

        int[] best = {-1, -1, -1, -1};

        // Find the best quadruplet for every sum
        for (ArrayList<Integer> pairs : map.values()) {

            if (pairs.size() < 2) {
                continue;
            }

            int first = pairs.get(0);

            int u = first / n;
            int v = first % n;

            int[] candidate = null;

            // First try to find a pair disjoint from the first pair
            for (int i = 1; i < pairs.size(); i++) {

                int p = pairs.get(i);

                int x = p / n;
                int y = p % n;

                if (x != u && x != v &&
                    y != u && y != v) {

                    candidate = new int[]{u, v, x, y};
                    break;
                }
            }

            // If the first pair has no disjoint partner
            if (candidate == null) {

                ArrayList<Integer> A = new ArrayList<>();
                ArrayList<Integer> B = new ArrayList<>();

                for (int i = 1; i < pairs.size(); i++) {

                    int p = pairs.get(i);

                    int x = p / n;
                    int y = p % n;

                    if (x == u) {
                        A.add(y);
                    } else if (y == v) {
                        B.add(x);
                    } else if (x == v) {
                        B.add(y);
                    }
                }

                // Find earliest compatible pair
                if (!B.isEmpty()) {

                    for (int x : A) {

                        int yFound = -1;

                        for (int y : B) {
                            if (x != y) {
                                yFound = y;
                                break;
                            }
                        }

                        if (yFound != -1) {

                            int c = Math.min(v, yFound);
                            int d = Math.max(v, yFound);

                            candidate = new int[]{u, x, c, d};
                            break;
                        }
                    }
                }
            }

            // Update globally lexicographically smallest answer
            if (candidate != null) {

                if (best[0] == -1 ||
                    compare(candidate, best) < 0) {

                    best = candidate;
                }
            }
        }

        ArrayList<Integer> ans = new ArrayList<>();

        for (int x : best) {
            ans.add(x);
        }

        return ans;
    }

    static int compare(int[] a, int[] b) {

        for (int i = 0; i < 4; i++) {

            if (a[i] != b[i]) {
                return Integer.compare(a[i], b[i]);
            }
        }

        return 0;
    }
}


