
import java.io.*;
import java.util.*;

public class Main {

    static final int MOD1 = 998244353;
    static final int MOD2 = 1004535809;
    static final int ROOT = 3;

    static final long INV_MOD1_MOD2 =
            modPow(MOD1, MOD2 - 2L, MOD2);

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
            } while (c <= 32);

            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            int value = 0;
            while (c > 32) {
                value = value * 10 + c - '0';
                c = read();
            }
            return value * sign;
        }

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= 32);

            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            long value = 0;
            while (c > 32) {
                value = value * 10 + c - '0';
                c = read();
            }
            return value * sign;
        }
    }

    static class DSU {
        int[] parent, size;

        DSU(int n) {
            parent = new int[n + 1];
            size = new int[n + 1];

            for (int i = 1; i <= n; i++) {
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

    static int[] head, to, next, adjEdge;
    static int edgePtr;

    static void addEdge(int u, int v, int id) {
        to[edgePtr] = v;
        adjEdge[edgePtr] = id;
        next[edgePtr] = head[u];
        head[u] = edgePtr++;
    }

    static long modPow(long a, long e, int mod) {
        long result = 1;

        while (e > 0) {
            if ((e & 1) != 0) {
                result = result * a % mod;
            }
            a = a * a % mod;
            e >>= 1;
        }

        return result;
    }

    static void ntt(int[] a, boolean invert, int mod) {
        int n = a.length;

        // Bit reversal
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;

            while ((j & bit) != 0) {
                j ^= bit;
                bit >>= 1;
            }

            j ^= bit;

            if (i < j) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }

        for (int len = 2; len <= n; len <<= 1) {
            long wlen = modPow(ROOT, (mod - 1L) / len, mod);

            if (invert) {
                wlen = modPow(wlen, mod - 2L, mod);
            }

            int half = len >> 1;

            for (int i = 0; i < n; i += len) {
                long w = 1;

                for (int j = 0; j < half; j++) {
                    int u = a[i + j];

                    int v = (int) (
                            (long) a[i + j + half] * w % mod
                    );

                    int x = u + v;
                    if (x >= mod) x -= mod;

                    int y = u - v;
                    if (y < 0) y += mod;

                    a[i + j] = x;
                    a[i + j + half] = y;

                    w = w * wlen % mod;
                }
            }
        }

        if (invert) {
            long invN = modPow(n, mod - 2L, mod);

            for (int i = 0; i < n; i++) {
                a[i] = (int) (a[i] * invN % mod);
            }
        }
    }

    // Computes f1*f2 + f1*f3 + f2*f3.
    // Coefficient s counts valid pairs of removed edges
    // whose costs add up to s.
    static int[] crossConvolution(
            int[][] freq,
            int size,
            int mod
    ) {
        int[] a = new int[size];
        int[] b = new int[size];
        int[] c = new int[size];

        for (int i = 0; i < freq[0].length; i++) {
            a[i] = freq[0][i] % mod;
            b[i] = freq[1][i] % mod;
            c[i] = freq[2][i] % mod;
        }

        ntt(a, false, mod);
        ntt(b, false, mod);
        ntt(c, false, mod);

        for (int i = 0; i < size; i++) {
            long x = (long) a[i] * b[i] % mod;
            x += (long) a[i] * c[i] % mod;
            if (x >= mod) x -= mod;

            x += (long) b[i] * c[i] % mod;
            if (x >= mod) x -= mod;

            a[i] = (int) x;
        }

        ntt(a, true, mod);
        return a;
    }

    static int lca(
            int u,
            int v,
            int[] depth,
            int[][] up
    ) {
        if (depth[u] < depth[v]) {
            int temp = u;
            u = v;
            v = temp;
        }

        int diff = depth[u] - depth[v];

        for (int j = 0; diff > 0; j++) {
            if ((diff & 1) != 0) {
                u = up[j][u];
            }
            diff >>= 1;
        }

        if (u == v) return u;

        for (int j = up.length - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }

    static void markPath(
            int u,
            int v,
            int[] diff,
            int[] depth,
            int[][] up
    ) {
        int w = lca(u, v, depth, up);

        diff[u]++;
        diff[v]++;
        diff[w] -= 2;
    }

    static void solve(FastScanner fs, StringBuilder out)
            throws Exception {

        int n = fs.nextInt();
        int r = fs.nextInt();
        int q = fs.nextInt();

        int[] U = new int[r];
        int[] V = new int[r];
        int[] C = new int[r];

        long totalCost = 0;
        int maxCost = 0;

        DSU dsu = new DSU(n);

        head = new int[n + 1];
        Arrays.fill(head, -1);

        to = new int[2 * (n - 1)];
        next = new int[2 * (n - 1)];
        adjEdge = new int[2 * (n - 1)];
        edgePtr = 0;

        int[] extra = new int[2];
        int extraCount = 0;

        // Construct an arbitrary spanning tree.
        for (int i = 0; i < r; i++) {
            U[i] = fs.nextInt();
            V[i] = fs.nextInt();
            C[i] = fs.nextInt();

            totalCost += C[i];
            maxCost = Math.max(maxCost, C[i]);

            if (dsu.union(U[i], V[i])) {
                addEdge(U[i], V[i], i);
                addEdge(V[i], U[i], i);
            } else {
                extra[extraCount++] = i;
            }
        }

        // Case 1: The original graph is already a tree.
        if (r == n - 1) {
            for (int i = 0; i < q; i++) {
                long k = fs.nextLong();
                out.append(k == 1 ? totalCost : -1).append('\n');
            }
            return;
        }

        // Build a rooted representation of the spanning tree.
        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        int[][] up = new int[LOG][n + 1];

        int[] parent = new int[n + 1];
        int[] depth = new int[n + 1];
        int[] parentEdge = new int[n + 1];
        int[] order = new int[n];

        int count = 1;
        order[0] = 1;

        for (int i = 0; i < count; i++) {
            int v = order[i];

            for (int e = head[v]; e != -1; e = next[e]) {
                int w = to[e];

                if (w == parent[v]) continue;

                parent[w] = v;
                parentEdge[w] = adjEdge[e];
                depth[w] = depth[v] + 1;

                order[count++] = w;
            }
        }

        for (int v = 1; v <= n; v++) {
            up[0][v] = parent[v];
        }

        for (int j = 1; j < LOG; j++) {
            for (int v = 1; v <= n; v++) {
                up[j][v] = up[j - 1][up[j - 1][v]];
            }
        }

        // Fundamental-cycle membership.
        int[] diff1 = new int[n + 1];
        int[] diff2 = new int[n + 1];

        markPath(
                U[extra[0]], V[extra[0]],
                diff1, depth, up
        );

        if (extraCount == 2) {
            markPath(
                    U[extra[1]], V[extra[1]],
                    diff2, depth, up
            );
        }

        // Accumulate path differences from children to parents.
        for (int i = n - 1; i > 0; i--) {
            int v = order[i];
            int p = parent[v];

            diff1[p] += diff1[v];
            diff2[p] += diff2[v];
        }

        int[] edgeMask = new int[r];

        edgeMask[extra[0]] = 1;

        if (extraCount == 2) {
            edgeMask[extra[1]] = 2;
        }

        for (int i = 1; i < n; i++) {
            int v = order[i];

            int mask = 0;

            if (diff1[v] > 0) mask |= 1;
            if (diff2[v] > 0) mask |= 2;

            edgeMask[parentEdge[v]] = mask;
        }

        // Case 2: Exactly one extra edge.
        // Every spanning tree removes one edge from the unique cycle.
        if (r == n) {
            int cycleLength = 0;
            int[] cycleCosts = new int[n];

            for (int i = 0; i < r; i++) {
                if (edgeMask[i] != 0) {
                    cycleCosts[cycleLength++] = C[i];
                }
            }

            Arrays.sort(cycleCosts, 0, cycleLength);

            for (int i = 0; i < q; i++) {
                long k = fs.nextLong();

                if (k < 1 || k > cycleLength) {
                    out.append(-1).append('\n');
                } else {
                    int removedCost =
                            cycleCosts[cycleLength - (int) k];

                    out.append(totalCost - removedCost)
                       .append('\n');
                }
            }

            return;
        }

        // Case 3: Exactly two extra edges.
        // Non-bridge edges belong to one of three series classes:
        // mask 1, mask 2, or mask 3.
        int[][] freq = new int[3][maxCost + 1];

        for (int i = 0; i < r; i++) {
            int mask = edgeMask[i];

            if (mask != 0) {
                freq[mask - 1][C[i]]++;
            }
        }

        int resultLength = 2 * maxCost + 1;

        int size = 1;
        while (size < resultLength) {
            size <<= 1;
        }

        // First NTT modulus.
        int[] result1 = crossConvolution(freq, size, MOD1);

        // Second NTT modulus.
        int[] result2 = crossConvolution(freq, size, MOD2);

        // CRT reconstruction gives exact pair counts.
        long[] suffix = new long[resultLength + 1];

        for (int s = resultLength - 1; s >= 0; s--) {
            long a = result1[s];
            long b = result2[s];

            long difference = (b - a) % MOD2;
            if (difference < 0) difference += MOD2;

            long multiplier =
                    difference * INV_MOD1_MOD2 % MOD2;

            long ways = a + (long) MOD1 * multiplier;

            suffix[s] = suffix[s + 1] + ways;
        }

        // The spanning-tree cost is:
        // totalCost - (cost of the two removed edges).
        // Therefore, kth smallest tree cost corresponds to
        // kth largest valid removed-edge cost sum.
        for (int i = 0; i < q; i++) {
            long k = fs.nextLong();

            if (k < 1 || k > suffix[0]) {
                out.append(-1).append('\n');
                continue;
            }

            int low = 0;
            int high = resultLength - 1;

            // Find the largest sum s such that suffix[s] >= k.
            while (low < high) {
                int mid = (low + high + 1) >>> 1;

                if (suffix[mid] >= k) {
                    low = mid;
                } else {
                    high = mid - 1;
                }
            }

            out.append(totalCost - low).append('\n');
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
