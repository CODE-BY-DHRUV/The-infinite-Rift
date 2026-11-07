
import java.io.*;
import java.util.*;

public class Main {

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

        String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int c;

            do {
                c = read();
            } while (c <= ' ');

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }

            return sb.toString();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    static class Node {
        int sum, min, max;

        Node(int sum, int min, int max) {
            this.sum = sum;
            this.min = min;
            this.max = max;
        }
    }

    static Node merge(Node a, Node b) {
        return new Node(
            a.sum + b.sum,
            Math.min(a.min, a.sum + b.min),
            Math.max(a.max, a.sum + b.max)
        );
    }

    static Node reverse(Node a) {
        return new Node(
            a.sum,
            a.sum - a.max,
            a.sum - a.min
        );
    }

    static final Node EMPTY = new Node(0, 0, 0);

    static class SegmentTree {
        int[] sum, min, max;
        int n;

        SegmentTree(int[] arr) {
            n = arr.length;

            sum = new int[4 * n];
            min = new int[4 * n];
            max = new int[4 * n];

            build(1, 0, n - 1, arr);
        }

        void build(int p, int l, int r, int[] arr) {
            if (l == r) {
                sum[p] = arr[l];
                min[p] = Math.min(0, arr[l]);
                max[p] = Math.max(0, arr[l]);
                return;
            }

            int mid = (l + r) >>> 1;

            build(p << 1, l, mid, arr);
            build(p << 1 | 1, mid + 1, r, arr);

            pull(p);
        }

        void pull(int p) {
            int L = p << 1;
            int R = L | 1;

            sum[p] = sum[L] + sum[R];

            min[p] = Math.min(
                min[L],
                sum[L] + min[R]
            );

            max[p] = Math.max(
                max[L],
                sum[L] + max[R]
            );
        }

        Node query(int p, int l, int r, int ql, int qr) {
            if (ql <= l && r <= qr) {
                return new Node(sum[p], min[p], max[p]);
            }

            int mid = (l + r) >>> 1;

            if (qr <= mid) {
                return query(p << 1, l, mid, ql, qr);
            }

            if (ql > mid) {
                return query(p << 1 | 1, mid + 1, r, ql, qr);
            }

            Node left = query(p << 1, l, mid, ql, qr);
            Node right = query(p << 1 | 1, mid + 1, r, ql, qr);

            return merge(left, right);
        }

        Node query(int l, int r) {
            if (l > r) return EMPTY;
            return query(1, 0, n - 1, l, r);
        }
    }

    static int n;
    static ArrayList<Integer>[] adj;

    static int[] parent, depth, heavy;
    static int[] head, pos, subtree;
    static int timer;

    static int[] value;
    static SegmentTree seg;

    static void buildHLD() {

        parent = new int[n];
        depth = new int[n];
        heavy = new int[n];
        head = new int[n];
        pos = new int[n];
        subtree = new int[n];

        Arrays.fill(parent, -1);
        Arrays.fill(heavy, -1);

        int[] order = new int[n];
        int[] stack = new int[n];

        int count = 0;
        int top = 0;

        stack[top++] = 0;
        parent[0] = 0;

        // Iterative DFS
        while (top > 0) {
            int u = stack[--top];
            order[count++] = u;

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                stack[top++] = v;
            }
        }

        // Calculate subtree sizes and heavy child
        for (int i = count - 1; i >= 0; i--) {
            int u = order[i];

            subtree[u] = 1;
            int largest = 0;

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                subtree[u] += subtree[v];

                if (subtree[v] > largest) {
                    largest = subtree[v];
                    heavy[u] = v;
                }
            }
        }

        // Assign HLD positions
        int[] nodeStack = new int[n];
        int[] headStack = new int[n];

        top = 0;
        nodeStack[top] = 0;
        headStack[top++] = 0;

        timer = 0;

        while (top > 0) {
            top--;

            int u = nodeStack[top];
            int h = headStack[top];

            while (u != -1) {
                head[u] = h;
                pos[u] = timer++;

                for (int v : adj[u]) {
                    if (v != parent[u] && v != heavy[u]) {
                        nodeStack[top] = v;
                        headStack[top++] = v;
                    }
                }

                u = heavy[u];
            }
        }
    }

    static Node pathQuery(int u, int v) {

        // left: path collected from original u upwards
        // right: path collected from original v upwards,
        //        but maintained in the correct final order.
        Node left = EMPTY;
        Node right = EMPTY;

        while (head[u] != head[v]) {

            if (depth[head[u]] >= depth[head[v]]) {

                // head[u] -> u is forward in HLD order.
                // We need u -> head[u], so reverse it.
                Node cur = seg.query(pos[head[u]], pos[u]);

                left = merge(left, reverse(cur));

                u = parent[head[u]];

            } else {

                // head[v] -> v is already in the required order.
                Node cur = seg.query(pos[head[v]], pos[v]);

                right = merge(cur, right);

                v = parent[head[v]];
            }
        }

        // Both nodes are now on the same chain.
        if (depth[u] >= depth[v]) {

            Node cur = seg.query(pos[v], pos[u]);

            left = merge(left, reverse(cur));

        } else {

            Node cur = seg.query(pos[u], pos[v]);

            right = merge(cur, right);
        }

        return merge(left, right);
    }

    static void solve(FastScanner fs, StringBuilder out)
            throws IOException {

        n = fs.nextInt();
        int q = fs.nextInt();

        adj = new ArrayList[n];

        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
        }

        for (int i = 0; i < n - 1; i++) {
            int u = fs.nextInt() - 1;
            int v = fs.nextInt() - 1;

            adj[u].add(v);
            adj[v].add(u);
        }

        // Parentheses are space-separated.
        value = new int[n];

        for (int i = 0; i < n; i++) {
            String token = fs.next();
            value[i] = token.charAt(0) == '(' ? 1 : -1;
        }

        buildHLD();

        int[] base = new int[n];

        for (int i = 0; i < n; i++) {
            base[pos[i]] = value[i];
        }

        seg = new SegmentTree(base);

        while (q-- > 0) {

            int u = fs.nextInt() - 1;
            int v = fs.nextInt() - 1;

            Node result = pathQuery(u, v);

            if (result.sum == 0 && result.min >= 0) {
                out.append("Yes\n");
            } else {
                out.append("No\n");
            }
        }
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {
            solve(fs, out);
        }

        System.out.print(out);
    }
}
