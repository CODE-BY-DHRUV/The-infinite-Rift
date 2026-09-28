
import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            int res = 0;
            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return res * sign;
        }
    }

    static int n;
    static int[] a;
    static int[] seg;
    static int[] next;
    static int[] dp;

    // Build segment tree storing maximum in each range
    static void build(int node, int l, int r) {
        if (l == r) {
            seg[node] = a[l];
            return;
        }

        int mid = (l + r) >>> 1;

        build(node << 1, l, mid);
        build(node << 1 | 1, mid + 1, r);

        seg[node] = Math.max(seg[node << 1], seg[node << 1 | 1]);
    }

    /*
     * Find the first index >= ql whose value >= value.
     */
    static int firstAtLeast(int node, int l, int r,
                            int ql, int value) {

        if (r < ql || seg[node] < value) {
            return -1;
        }

        if (l == r) {
            return l;
        }

        int mid = (l + r) >>> 1;

        int left = firstAtLeast(
                node << 1,
                l,
                mid,
                ql,
                value
        );

        if (left != -1) {
            return left;
        }

        return firstAtLeast(
                node << 1 | 1,
                mid + 1,
                r,
                ql,
                value
        );
    }

    static int firstAtLeast(int pos, int value) {
        if (pos >= n) {
            return -1;
        }

        return firstAtLeast(1, 0, n - 1, pos, value);
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            n = fs.nextInt();

            a = new int[n];

            for (int i = 0; i < n; i++) {
                a[i] = fs.nextInt();
            }

            if (n == 1) {
                out.append(1).append('\n');
                continue;
            }

            /*
             * ----------------------------------------------------
             * 1. Build next[i]
             *
             * next[i] = first j > i such that a[j] >= a[i]
             *
             * Monotonic stack gives O(N).
             * ----------------------------------------------------
             */

            next = new int[n];

            int[] stack = new int[n];
            int top = 0;

            for (int i = n - 1; i >= 0; i--) {

                while (top > 0 && a[stack[top - 1]] < a[i]) {
                    top--;
                }

                next[i] = (top == 0) ? -1 : stack[top - 1];

                stack[top++] = i;
            }

            /*
             * ----------------------------------------------------
             * 2. dp[i] = number of elements selected if we start
             *    pseudo-sort from index i.
             * ----------------------------------------------------
             */

            dp = new int[n];

            for (int i = n - 1; i >= 0; i--) {
                dp[i] = 1;

                if (next[i] != -1) {
                    dp[i] += dp[next[i]];
                }
            }

            /*
             * ----------------------------------------------------
             * 3. Build the original greedy sequence.
             *
             * selected[] contains the indices selected by
             * pseudo_sort(a).
             * ----------------------------------------------------
             */

            int[] selected = new int[n];
            int selectedCount = 0;

            for (int i = 0; i < n; i++) {

                if (selectedCount == 0 ||
                    a[i] >= a[selected[selectedCount - 1]]) {

                    selected[selectedCount++] = i;
                }
            }

            /*
             * No deletion.
             */
            int answer = selectedCount;

            /*
             * Segment tree is needed for finding:
             *
             * first index j > deletedIndex
             * such that a[j] >= previousSelectedValue
             *
             * Build it now.
             */
            seg = new int[4 * n];
            build(1, 0, n - 1);

            /*
             * ----------------------------------------------------
             * 4. Try deleting every selected element.
             *
             * If we delete selected[q]:
             *
             * prefix = q elements remain before it.
             *
             * If q == 0:
             *     index 0 is deleted, so index 1 becomes
             *     the first element.
             *
             * Otherwise:
             *     previous selected value = a[selected[q - 1]]
             *
             * Find first position after selected[q] with
             * value >= previous selected value.
             * ----------------------------------------------------
             */

            for (int q = 0; q < selectedCount; q++) {

                int deleted = selected[q];

                int candidate;

                if (q == 0) {

                    // Delete first selected element.
                    candidate = dp[1];

                } else {

                    int previousIndex = selected[q - 1];
                    int previousValue = a[previousIndex];

                    int start = firstAtLeast(
                            deleted + 1,
                            previousValue
                    );

                    // q elements were already selected
                    // before the deleted element.
                    candidate = q;

                    if (start != -1) {
                        candidate += dp[start];
                    }
                }

                answer = Math.max(answer, candidate);
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}

