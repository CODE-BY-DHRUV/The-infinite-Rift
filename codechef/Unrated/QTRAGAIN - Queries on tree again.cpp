
import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;
    static final int MAXY = 60;

    static int n, q;

    static int[] parent;

    /*
     * down[u * 61 + d]
     *
     * Stores the contribution made by updates originating
     * at node u to a descendant exactly d edges below u.
     *
     * Example:
     * update(u, 3):
     *
     * down[u][0] += 8
     * down[u][1] += 4
     * down[u][2] += 2
     * down[u][3] += 1
     */
    static int[] down;

    /*
     * value[u] stores contributions from updates whose source
     * is a descendant of u.
     *
     * We directly add those contributions while processing
     * an update.
     */
    static int[] value;

    static long[] pow2 = new long[MAXY + 1];

    // ------------------------------------------------------------
    // Fast Scanner
    // ------------------------------------------------------------

    static class FastScanner {

        private final InputStream in = System.in;

        private final byte[] buffer = new byte[1 << 16];

        private int ptr = 0;
        private int len = 0;

        private int read() throws IOException {

            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;

                if (len <= 0) {
                    return -1;
                }
            }

            return buffer[ptr++];
        }

        int nextInt() throws IOException {

            int c;

            do {
                c = read();
            } while (c <= ' ');

            int res = 0;

            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return res;
        }
    }

    // ------------------------------------------------------------
    // Add modulo
    // ------------------------------------------------------------

    static int add(int a, long b) {

        long res = a + b;

        if (res >= MOD) {
            res -= MOD;
        }

        return (int) res;
    }

    // ------------------------------------------------------------
    // Update
    // ------------------------------------------------------------

    static void update(int x, int y) {

        /*
         * PART 1:
         *
         * Store the contribution of this update to descendants
         * of x.
         *
         * This MUST be done independently of the ancestor traversal.
         */
        int base = x * (MAXY + 1);

        for (int d = 0; d <= y; d++) {

            long contribution = pow2[y - d];

            int index = base + d;

            down[index] += (int) contribution;

            if (down[index] >= MOD) {
                down[index] -= MOD;
            }
        }

        /*
         * PART 2:
         *
         * Directly add the contribution to ancestors of x.
         *
         * d = 1 means parent of x.
         *
         * d = 2 means grandparent, etc.
         *
         * We deliberately start at d=1 because d=0 (x itself)
         * is handled through down[x][0].
         */
        int cur = x;

        for (int d = 1; d <= y; d++) {

            cur = parent[cur];

            if (cur == 0) {
                break;
            }

            long contribution = pow2[y - d];

            value[cur] += (int) contribution;

            if (value[cur] >= MOD) {
                value[cur] -= MOD;
            }
        }
    }

    // ------------------------------------------------------------
    // Query
    // ------------------------------------------------------------

    static long query(int x) {

        /*
         * value[x]:
         *
         * Contributions from updates whose source is a
         * descendant of x.
         */
        long ans = value[x];

        /*
         * Now walk through ancestors of x.
         *
         * If u is d edges above x, then down[u][d] contains
         * all contributions from updates originating at u
         * that reach x.
         */
        int cur = x;

        for (int d = 0; d <= MAXY; d++) {

            int index = cur * (MAXY + 1) + d;

            ans += down[index];

            if (ans >= MOD) {
                ans -= MOD;
            }

            if (cur == 1) {
                break;
            }

            cur = parent[cur];
        }

        return ans;
    }

    // ------------------------------------------------------------
    // Main
    // ------------------------------------------------------------

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();

        StringBuilder out = new StringBuilder();

        /*
         * Precompute:
         *
         * 2^0, 2^1, ..., 2^60
         */
        pow2[0] = 1;

        for (int i = 1; i <= MAXY; i++) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        int T = fs.nextInt();

        while (T-- > 0) {

            n = fs.nextInt();
            q = fs.nextInt();

            /*
             * Tree using adjacency arrays.
             */
            int[] head = new int[n + 1];

            int[] to = new int[2 * Math.max(0, n - 1)];

            int[] next = new int[2 * Math.max(0, n - 1)];

            Arrays.fill(head, -1);

            int edgeCount = 0;

            for (int i = 0; i < n - 1; i++) {

                int u = fs.nextInt();
                int v = fs.nextInt();

                to[edgeCount] = v;
                next[edgeCount] = head[u];
                head[u] = edgeCount++;

                to[edgeCount] = u;
                next[edgeCount] = head[v];
                head[v] = edgeCount++;
            }

            /*
             * Build parent[] iteratively.
             *
             * The tree is rooted at 1.
             */
            parent = new int[n + 1];

            int[] stack = new int[n];

            int top = 0;

            stack[top++] = 1;

            parent[1] = 0;

            while (top > 0) {

                int u = stack[--top];

                for (int e = head[u]; e != -1; e = next[e]) {

                    int v = to[e];

                    if (v == parent[u]) {
                        continue;
                    }

                    parent[v] = u;

                    stack[top++] = v;
                }
            }

            /*
             * 61 values per node.
             *
             * int is enough because every value is maintained
             * modulo 1e9+7.
             */
            down = new int[(n + 1) * (MAXY + 1)];

            /*
             * Contributions from descendant-source updates
             * to each node.
             */
            value = new int[n + 1];

            /*
             * Process queries.
             */
            while (q-- > 0) {

                int type = fs.nextInt();

                int x = fs.nextInt();

                if (type == 1) {

                    int y = fs.nextInt();

                    update(x, y);

                } else {

                    out.append(query(x))
                       .append('\n');
                }
            }
        }

        System.out.print(out);
    }
}


 