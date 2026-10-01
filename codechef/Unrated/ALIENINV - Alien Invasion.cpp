import java.io.*;
import java.util.*;

public class Main {

    static int n;
    static ArrayList<Integer>[] g;

    static double[] solve() {
        double[] ans = new double[n];

        int[] parent = new int[n];
        int[] top = new int[n];
        int[] sub = new int[n];
        int[] order = new int[n];

        for (int root = 0; root < n; root++) {

            // Iterative DFS/BFS to root the tree at 'root'
            Arrays.fill(parent, -2);
            Arrays.fill(top, -1);

            int len = 0;
            order[len++] = root;
            parent[root] = -1;

            for (int i = 0; i < len; i++) {
                int u = order[i];

                for (int v : g[u]) {
                    if (parent[v] != -2) continue;

                    parent[v] = u;

                    // First child of root on the path root -> v
                    if (u == root)
                        top[v] = v;
                    else
                        top[v] = top[u];

                    order[len++] = v;
                }
            }

            // Calculate subtree sizes
            Arrays.fill(sub, 1);

            for (int i = n - 1; i > 0; i--) {
                int u = order[i];
                sub[parent[u]] += sub[u];
            }

            double expected = 1.0; // v itself

            // Calculate contribution of every u != root
            for (int i = 1; i < n; i++) {
                int u = order[i];

                int firstChild = top[u];

                // Size of the component containing root
                // after cutting root-firstChild.
                int rootSide = n - sub[firstChild];

                // Probability(u is invaded before root)
                double probability =
                        (double) rootSide /
                        (rootSide + sub[u]);

                expected += probability;
            }

            ans[root] = expected;
        }

        return ans;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {
            n = fs.nextInt();

            g = new ArrayList[n];
            for (int i = 0; i < n; i++) {
                g[i] = new ArrayList<>();
            }

            for (int i = 0; i < n - 1; i++) {
                int u = fs.nextInt() - 1;
                int v = fs.nextInt() - 1;

                g[u].add(v);
                g[v].add(u);
            }

            double[] ans = solve();

            for (int i = 0; i < n; i++) {
                if (i > 0) out.append(' ');
                out.append(String.format(Locale.US, "%.10f", ans[i]));
            }
            out.append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        FastScanner(InputStream is) {
            in = is;
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
}