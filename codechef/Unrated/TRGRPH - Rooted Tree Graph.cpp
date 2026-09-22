import java.io.*;
import java.util.*;

public class Main {

    static class Edge {
        int u, v;

        Edge(int u, int v) {
            this.u = u;
            this.v = v;
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int Q = fs.nextInt();

        while (Q-- > 0) {
            int n = fs.nextInt();
            int m = fs.nextInt();

            ArrayList<Integer>[] graph = new ArrayList[n];

            for (int i = 0; i < n; i++) {
                graph[i] = new ArrayList<>();
            }

            Edge[] edges = new Edge[m];
            int[] degree = new int[n];

            for (int i = 0; i < m; i++) {
                int u = fs.nextInt() - 1;
                int v = fs.nextInt() - 1;

                graph[u].add(v);
                graph[v].add(u);

                degree[u]++;
                degree[v]++;

                edges[i] = new Edge(u, v);
            }

            // ---------------------------------------------------------
            // 1. Sort vertices by decreasing degree.
            // ---------------------------------------------------------
            Integer[] order = new Integer[n];

            for (int i = 0; i < n; i++) {
                order[i] = i;
            }

            Arrays.sort(order, new Comparator<Integer>() {
                @Override
                public int compare(Integer a, Integer b) {
                    if (degree[a] != degree[b]) {
                        return Integer.compare(degree[b], degree[a]);
                    }
                    return Integer.compare(a, b);
                }
            });

            // position[v] = position of v in degree ordering
            int[] position = new int[n];

            for (int i = 0; i < n; i++) {
                position[order[i]] = i;
            }

            // ---------------------------------------------------------
            // 2. Construct candidate tree.
            // ---------------------------------------------------------
            int[] parent = new int[n];
            Arrays.fill(parent, -1);

            boolean possible = true;

            // First vertex is the root.
            parent[order[0]] = -1;

            for (int i = 1; i < n && possible; i++) {
                int v = order[i];

                int best = -1;
                int bestPosition = -1;

                /*
                 * Find the neighbor of v that occurs LAST among
                 * the vertices before v in the degree ordering.
                 */
                for (int u : graph[v]) {
                    if (position[u] < i) {
                        if (position[u] > bestPosition) {
                            bestPosition = position[u];
                            best = u;
                        }
                    }
                }

                // Every non-root vertex must have a parent.
                if (best == -1) {
                    possible = false;
                    break;
                }

                parent[v] = best;
            }

            if (!possible) {
                out.append("NO\n");
                continue;
            }

            // ---------------------------------------------------------
            // 3. Build the candidate tree.
            // ---------------------------------------------------------
            ArrayList<Integer>[] tree = new ArrayList[n];

            for (int i = 0; i < n; i++) {
                tree[i] = new ArrayList<>();
            }

            int root = order[0];

            for (int v = 0; v < n; v++) {
                if (parent[v] != -1) {
                    tree[v].add(parent[v]);
                    tree[parent[v]].add(v);
                }
            }

            // ---------------------------------------------------------
            // 4. DFS the tree.
            //
            // Compute:
            // depth[v]
            // subtreeSize[v]
            // tin[v], tout[v]
            // ---------------------------------------------------------
            int[] depth = new int[n];
            int[] tin = new int[n];
            int[] tout = new int[n];
            int[] subtree = new int[n];

            int timer = 0;

            // Iterative DFS to avoid stack overflow.
            int[] stack = new int[2 * n];
            int[] parentDfs = new int[n];
            int[] iter = new int[n];

            Arrays.fill(parentDfs, -2);
            parentDfs[root] = -1;

            int top = 0;
            stack[top++] = root;

            while (top > 0) {
                int v = stack[top - 1];

                if (iter[v] == 0) {
                    tin[v] = timer++;
                    subtree[v] = 1;
                }

                if (iter[v] < tree[v].size()) {
                    int u = tree[v].get(iter[v]++);

                    if (u == parentDfs[v]) {
                        continue;
                    }

                    parentDfs[u] = v;
                    depth[u] = depth[v] + 1;
                    stack[top++] = u;
                } else {
                    tout[v] = timer - 1;
                    top--;

                    if (parentDfs[v] != -1) {
                        subtree[parentDfs[v]] += subtree[v];
                    }
                }
            }

            // ---------------------------------------------------------
            // 5. Verify every original graph edge.
            //
            // For an ancestor graph, every graph edge must connect
            // ancestor <-> descendant.
            // ---------------------------------------------------------
            for (Edge e : edges) {
                int u = e.u;
                int v = e.v;

                boolean uAncestorV =
                        tin[u] <= tin[v] && tout[v] <= tout[u];

                boolean vAncestorU =
                        tin[v] <= tin[u] && tout[u] <= tout[v];

                if (!uAncestorV && !vAncestorU) {
                    possible = false;
                    break;
                }
            }

            // ---------------------------------------------------------
            // 6. Verify every vertex has exactly the correct degree.
            //
            // In an ancestor graph:
            //
            // degree(v)
            // = number of ancestors
            // + number of descendants
            // = depth[v] + subtree[v] - 1
            // ---------------------------------------------------------
            if (possible) {
                for (int v = 0; v < n; v++) {
                    int expectedDegree =
                            depth[v] + subtree[v] - 1;

                    if (expectedDegree != degree[v]) {
                        possible = false;
                        break;
                    }
                }
            }

            if (!possible) {
                out.append("NO\n");
            } else {
                out.append("YES\n");

                for (int v = 0; v < n; v++) {
                    out.append(parent[v] == -1 ? 0 : parent[v] + 1);

                    if (v + 1 < n) {
                        out.append(' ');
                    }
                }

                out.append('\n');
            }
        }

        System.out.print(out);
    }

    // -------------------------------------------------------------
    // Fast Scanner
    // -------------------------------------------------------------
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        FastScanner(InputStream in) {
            this.in = in;
        }

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
