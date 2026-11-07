
import java.io.*;
import java.util.*;

public class Main {

    static final long INF = Long.MAX_VALUE;

    static class Edge {
        int u, v, id;
        long w;
        boolean inMST;

        Edge(int u, int v, long w, int id) {
            this.u = u;
            this.v = v;
            this.w = w;
            this.id = id;
        }
    }

    static class DSU {
        int[] parent, size;

        DSU(int n) {
            parent = new int[n];
            size = new int[n];

            for (int i = 0; i < n; i++) {
                parent[i] = i;
                size[i] = 1;
            }
        }

        int find(int x) {
            while (parent[x] != x) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        }

        boolean union(int a, int b) {
            a = find(a);
            b = find(b);

            if (a == b) return false;

            if (size[a] < size[b]) {
                int temp = a;
                a = b;
                b = temp;
            }

            parent[b] = a;
            size[a] += size[b];

            return true;
        }
    }

    static class SegmentTree {

        int n;
        long[] lazy;

        SegmentTree(int n) {
            this.n = n;
            lazy = new long[4 * n + 5];
            Arrays.fill(lazy, INF);
        }

        // Range minimum update: [ql, qr]
        void update(int ql, int qr, long val) {
            if (ql > qr) return;
            update(1, 0, n - 1, ql, qr, val);
        }

        void update(int node, int l, int r,
                    int ql, int qr, long val) {

            if (ql <= l && r <= qr) {
                lazy[node] = Math.min(lazy[node], val);
                return;
            }

            int mid = (l + r) >>> 1;

            if (ql <= mid) {
                update(node * 2, l, mid, ql, qr, val);
            }

            if (qr > mid) {
                update(node * 2 + 1, mid + 1, r,
                       ql, qr, val);
            }
        }

        // Point query
        long query(int idx) {
            int node = 1;
            int l = 0;
            int r = n - 1;

            long ans = INF;

            while (true) {

                ans = Math.min(ans, lazy[node]);

                if (l == r) break;

                int mid = (l + r) >>> 1;

                if (idx <= mid) {
                    node *= 2;
                    r = mid;
                } else {
                    node = node * 2 + 1;
                    l = mid + 1;
                }
            }

            return ans;
        }
    }

    static class HLD {

        int n;

        ArrayList<Edge>[] adj;

        int[] parent;
        int[] depth;
        int[] subtree;
        int[] heavy;
        int[] head;
        int[] pos;

        int[] parentEdge;

        SegmentTree seg;

        HLD(int n) {

            this.n = n;

            adj = new ArrayList[n];

            for (int i = 0; i < n; i++) {
                adj[i] = new ArrayList<>();
            }

            parent = new int[n];
            depth = new int[n];
            subtree = new int[n];
            heavy = new int[n];
            head = new int[n];
            pos = new int[n];
            parentEdge = new int[n];

            Arrays.fill(heavy, -1);
            Arrays.fill(parentEdge, -1);
        }

        void addEdge(Edge e) {
            adj[e.u].add(e);
            adj[e.v].add(e);
        }

        void build() {

            int[] order = new int[n];
            int[] stack = new int[n];

            Arrays.fill(parent, -2);

            int top = 0;
            int count = 0;

            stack[top++] = 0;
            parent[0] = -1;

            // Iterative DFS
            while (top > 0) {

                int u = stack[--top];

                order[count++] = u;

                for (Edge e : adj[u]) {

                    int v = e.u ^ e.v ^ u;

                    if (v == parent[u]) continue;

                    parent[v] = u;
                    parentEdge[v] = e.id;
                    depth[v] = depth[u] + 1;

                    stack[top++] = v;
                }
            }

            // Calculate subtree sizes and heavy children
            Arrays.fill(subtree, 1);

            for (int i = n - 1; i > 0; i--) {

                int u = order[i];
                int p = parent[u];

                subtree[p] += subtree[u];

                if (heavy[p] == -1 ||
                    subtree[u] > subtree[heavy[p]]) {

                    heavy[p] = u;
                }
            }

            // Heavy-Light Decomposition
            int timer = 0;

            for (int i = 0; i < n; i++) {

                int start = order[i];

                if (parent[start] != -1 &&
                    heavy[parent[start]] == start) {
                    continue;
                }

                for (int u = start; u != -1; u = heavy[u]) {

                    head[u] = start;
                    pos[u] = timer++;
                }
            }

            seg = new SegmentTree(n);
        }

        // Apply minimum replacement weight to every
        // tree edge on the path from u to v.
        void updatePath(int u, int v, long w) {

            while (head[u] != head[v]) {

                if (depth[head[u]] < depth[head[v]]) {
                    int temp = u;
                    u = v;
                    v = temp;
                }

                seg.update(
                    pos[head[u]],
                    pos[u],
                    w
                );

                u = parent[head[u]];
            }

            if (u == v) return;

            if (depth[u] > depth[v]) {
                int temp = u;
                u = v;
                v = temp;
            }

            // Exclude the LCA because positions represent
            // the edge connecting each node to its parent.
            seg.update(
                pos[u] + 1,
                pos[v],
                w
            );
        }

        long getReplacement(int node) {
            return seg.query(pos[node]);
        }
    }

    static void solve(FastScanner fs, StringBuilder out)
            throws IOException {

        int n = fs.nextInt();
        int e = fs.nextInt();

        Edge[] edges = new Edge[e];

        for (int i = 0; i < e; i++) {

            int u = fs.nextInt() - 1;
            int v = fs.nextInt() - 1;
            long w = fs.nextLong();

            edges[i] = new Edge(u, v, w, i);
        }

        // Kruskal's algorithm
        Arrays.sort(edges, (a, b) ->
            Long.compare(a.w, b.w)
        );

        DSU dsu = new DSU(n);

        HLD hld = new HLD(n);

        long mstWeight = 0;
        int selected = 0;

        for (Edge edge : edges) {

            if (dsu.union(edge.u, edge.v)) {

                edge.inMST = true;

                mstWeight += edge.w;
                selected++;

                hld.addEdge(edge);
            }
        }

        // Original graph is disconnected
        if (selected != n - 1) {

            for (int i = 0; i < e; i++) {
                out.append(-1).append('\n');
            }

            return;
        }

        hld.build();

        // Process every non-MST edge
        for (Edge edge : edges) {

            if (!edge.inMST) {

                hld.updatePath(
                    edge.u,
                    edge.v,
                    edge.w
                );
            }
        }

        // Store answers in original input order
        long[] answer = new long[e];

        Arrays.fill(answer, mstWeight);

        for (Edge edge : edges) {

            if (edge.inMST) {

                int child;

                if (hld.parent[edge.u] == edge.v) {
                    child = edge.u;
                } else {
                    child = edge.v;
                }

                long replacement =
                    hld.getReplacement(child);

                if (replacement == INF) {
                    answer[edge.id] = -1;
                } else {
                    answer[edge.id] =
                        mstWeight - edge.w + replacement;
                }
            }
        }

        for (int i = 0; i < e; i++) {
            out.append(answer[i]).append('\n');
        }
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner(System.in);

        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {
            solve(fs, out);
        }

        System.out.print(out);
    }

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

                if (len <= 0) return -1;
            }

            return buffer[ptr++];
        }

        String next() throws IOException {

            StringBuilder sb = new StringBuilder();

            int c;

            do {
                c = read();
            } while (c <= 32 && c != -1);

            while (c > 32) {
                sb.append((char) c);
                c = read();
            }

            return sb.toString();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        long nextLong() throws IOException {
            return Long.parseLong(next());
        }
    }
}
