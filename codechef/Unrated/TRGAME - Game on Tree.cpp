
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

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();
        StringBuilder output = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();

            int[] head = new int[n];
            int[] to = new int[2 * (n - 1)];
            int[] next = new int[2 * (n - 1)];

            Arrays.fill(head, -1);

            int edgeCnt = 0;

            for (int i = 0; i < n - 1; i++) {
                int u = fs.nextInt() - 1;
                int v = fs.nextInt() - 1;

                to[edgeCnt] = v;
                next[edgeCnt] = head[u];
                head[u] = edgeCnt++;

                to[edgeCnt] = u;
                next[edgeCnt] = head[v];
                head[v] = edgeCnt++;
            }

            // If n is odd, Bob wins for every x.
            if ((n & 1) == 1) {
                for (int i = 0; i < n; i++) {
                    output.append('0');
                }
                output.append('\n');
                continue;
            }

            /*
             * Root the tree at vertex 0.
             *
             * parent[u] = parent of u
             * order[]   = DFS/BFS order
             */
            int[] parent = new int[n];
            int[] order = new int[n];

            Arrays.fill(parent, -2);

            parent[0] = -1;

            int size = 0;
            order[size++] = 0;

            for (int i = 0; i < size; i++) {
                int u = order[i];

                for (int e = head[u]; e != -1; e = next[e]) {
                    int v = to[e];

                    if (v == parent[u]) {
                        continue;
                    }

                    parent[v] = u;
                    order[size++] = v;
                }
            }

            // Calculate subtree sizes.
            int[] sub = new int[n];

            Arrays.fill(sub, 1);

            for (int i = n - 1; i > 0; i--) {
                int u = order[i];
                sub[parent[u]] += sub[u];
            }

            /*
             * largest[u] =
             * maximum component size after deleting u.
             */
            int[] largest = new int[n];

            for (int u = 0; u < n; u++) {

                // Component containing parent[u].
                if (parent[u] != -1) {
                    largest[u] = n - sub[u];
                } else {
                    largest[u] = 0;
                }

                // Components corresponding to each child.
                for (int e = head[u]; e != -1; e = next[e]) {

                    int v = to[e];

                    if (parent[v] == u) {
                        largest[u] = Math.max(largest[u], sub[v]);
                    }
                }
            }

            /*
             * Alice wins iff every component after removing u
             * has size <= n/2.
             */
            int half = n / 2;

            for (int u = 0; u < n; u++) {
                if (largest[u] <= half) {
                    output.append('1');
                } else {
                    output.append('0');
                }
            }

            output.append('\n');
        }

        System.out.print(output);
    }
}


