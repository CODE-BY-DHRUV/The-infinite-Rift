
import java.io.*;
import java.util.*;

public class Main {
    static final long MOD = 1_000_000_007L;

    // State combination for two groups of components.
    static int combine(int a, int b) {
        if (a == 4 || b == 4) return 4;
        if (a == 0) return b;
        if (b == 0) return a;

        // Two black-only groups or two red-only groups.
        if (a == b && (a == 1 || a == 2)) return a;

        // Different nonempty categories guarantee separation.
        return 4;
    }

    static int category(int blacks, int reds) {
        if (blacks == 0 && reds == 0) return 0;
        if (blacks > 0 && reds > 0) return 3;
        if (blacks > 0) return 1;
        return 2;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder output = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            int n = fs.nextInt();

            // Memory-efficient adjacency list.
            int[] head = new int[n + 1];
            Arrays.fill(head, -1);

            int[] to = new int[2 * n];
            int[] next = new int[2 * n];
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

            int[] color = new int[n + 1];
            int totalBlack = 0, totalRed = 0;

            for (int i = 1; i <= n; i++) {
                color[i] = fs.nextInt();
                if (color[i] == 1) totalBlack++;
                if (color[i] == 2) totalRed++;
            }

            // Build parent array and traversal order iteratively.
            int[] parent = new int[n + 1];
            int[] order = new int[n];
            int[] stack = new int[n];
            int top = 0, size = 0;

            stack[top++] = 1;
            parent[1] = -1;

            while (top > 0) {
                int u = stack[--top];
                order[size++] = u;

                for (int e = head[u]; e != -1; e = next[e]) {
                    int v = to[e];
                    if (v == parent[u]) continue;

                    parent[v] = u;
                    stack[top++] = v;
                }
            }

            // Count black and red vertices in each subtree.
            int[] subBlack = new int[n + 1];
            int[] subRed = new int[n + 1];

            for (int u = 1; u <= n; u++) {
                if (color[u] == 1) subBlack[u] = 1;
                if (color[u] == 2) subRed[u] = 1;
            }

            for (int i = size - 1; i >= 0; i--) {
                int u = order[i];

                if (parent[u] > 0) {
                    subBlack[parent[u]] += subBlack[u];
                    subRed[parent[u]] += subRed[u];
                }
            }

            // dp[u][s]: connected uncolored sets rooted at u,
            // classified by the components below the set.
            long[][] dp = new long[n + 1][5];

            for (int i = size - 1; i >= 0; i--) {
                int u = order[i];

                // W cannot contain a colored vertex.
                if (color[u] != 0) continue;

                long[] cur = new long[5];
                cur[0] = 1; // Initially W = {u}.

                for (int e = head[u]; e != -1; e = next[e]) {
                    int v = to[e];

                    if (parent[v] != u) continue;

                    long[] nxt = new long[5];

                    int childCategory =
                        category(subBlack[v], subRed[v]);

                    // Option 1: Exclude the child subtree from W.
                    for (int s = 0; s < 5; s++) {
                        if (cur[s] == 0) continue;

                        int ns = combine(s, childCategory);
                        nxt[ns] = (nxt[ns] + cur[s]) % MOD;
                    }

                    // Option 2: Include a connected set rooted at v.
                    for (int s = 0; s < 5; s++) {
                        if (cur[s] == 0) continue;

                        for (int t = 0; t < 5; t++) {
                            if (dp[v][t] == 0) continue;

                            int ns = combine(s, t);

                            nxt[ns] = (
                                nxt[ns] + cur[s] * dp[v][t]
                            ) % MOD;
                        }
                    }

                    cur = nxt;
                }

                dp[u] = cur;
            }

            // Add the component outside each subtree.
            long answer = 0;

            for (int u = 1; u <= n; u++) {
                if (color[u] != 0) continue;

                int outsideCategory = 0;

                if (parent[u] > 0) {
                    outsideCategory = category(
                        totalBlack - subBlack[u],
                        totalRed - subRed[u]
                    );
                }

                for (int s = 0; s < 5; s++) {
                    if (combine(s, outsideCategory) == 4) {
                        answer = (answer + dp[u][s]) % MOD;
                    }
                }
            }

            output.append(answer).append('\n');
        }

        System.out.print(output);
    }

    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        FastScanner(InputStream in) {
            this.in = in;
        }

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
            } while (c <= ' ' && c != -1);

            int value = 0;
            while (c >= '0' && c <= '9') {
                value = value * 10 + c - '0';
                c = read();
            }
            return value;
        }
    }
}
