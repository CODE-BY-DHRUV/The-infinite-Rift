
import java.util.*;

class Solution {

    static class Disc {
        int r, h;

        Disc(int r, int h) {
            this.r = r;
            this.h = h;
        }
    }

    static class Fenwick {
        int[] tree;

        Fenwick(int n) {
            tree = new int[n + 1];
        }

        int query(int idx) {
            int ans = 0;

            while (idx > 0) {
                ans = Math.max(ans, tree[idx]);
                idx -= idx & -idx;
            }

            return ans;
        }

        void update(int idx, int value) {
            while (idx < tree.length) {
                tree[idx] = Math.max(tree[idx], value);
                idx += idx & -idx;
            }
        }
    }

    // GFG expects this exact method name
    public int maxStackHeight(int[] r, int[] h) {

        int n = r.length;

        Disc[] discs = new Disc[n];

        for (int i = 0; i < n; i++) {
            discs[i] = new Disc(r[i], h[i]);
        }

        // Radius ascending
        // Same radius -> height descending
        Arrays.sort(discs, (a, b) -> {
            if (a.r != b.r) {
                return Integer.compare(a.r, b.r);
            }
            return Integer.compare(b.h, a.h);
        });

        // h[i] <= 1000
        Fenwick bit = new Fenwick(1000);

        int answer = 0;

        for (Disc d : discs) {

            // Need height strictly smaller
            int bestBelow = bit.query(d.h - 1);

            int currentHeight = bestBelow + d.h;

            bit.update(d.h, currentHeight);

            answer = Math.max(answer, currentHeight);
        }

        return answer;
    }
}
