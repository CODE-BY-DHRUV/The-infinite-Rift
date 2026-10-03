import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    static class Fence {
        long x1, y1, x2, y2;

        Fence(long x1, long y1, long x2, long y2) {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;
        }
    }

    static class DSU {
        int[] parent;
        int[] size;

        DSU(int n) {
            parent = new int[n];
            size = new int[n];

            for (int i = 0; i < n; i++) {
                parent[i] = i;
                size[i] = 1;
            }
        }

        int find(int x) {
            if (parent[x] == x)
                return x;

            return parent[x] = find(parent[x]);
        }

        void union(int a, int b) {
            a = find(a);
            b = find(b);

            if (a == b)
                return;

            if (size[a] < size[b]) {
                int temp = a;
                a = b;
                b = temp;
            }

            parent[b] = a;
            size[a] += size[b];
        }
    }

    /*
     * Returns true if the vertical boundary
     *
     * x = x
     *
     * between y1 and y2 is blocked by a fence.
     */
    static boolean verticalBlocked(
            long x,
            long y1,
            long y2,
            Fence[] fences) {

        for (Fence f : fences) {

            // Left or right side of rectangle
            if ((x == f.x1 || x == f.x2)
                    && y1 >= f.y1
                    && y2 <= f.y2) {

                return true;
            }
        }

        return false;
    }

    /*
     * Returns true if the horizontal boundary
     *
     * y = y
     *
     * between x1 and x2 is blocked by a fence.
     */
    static boolean horizontalBlocked(
            long y,
            long x1,
            long x2,
            Fence[] fences) {

        for (Fence f : fences) {

            // Bottom or top side of rectangle
            if ((y == f.y1 || y == f.y2)
                    && x1 >= f.x1
                    && x2 <= f.x2) {

                return true;
            }
        }

        return false;
    }

    static long mod(long x) {
        x %= MOD;

        if (x < 0)
            x += MOD;

        return x;
    }

    static long modPow(long a, long e) {

        long result = 1;

        while (e > 0) {

            if ((e & 1) != 0) {
                result = result * a % MOD;
            }

            a = a * a % MOD;
            e >>= 1;
        }

        return result;
    }

    static long solve(
            long N,
            long M,
            Fence[] fences) {

        /*
         * Coordinate compression.
         */
        TreeSet<Long> xSet = new TreeSet<>();
        TreeSet<Long> ySet = new TreeSet<>();

        xSet.add(0L);
        xSet.add(N);

        ySet.add(0L);
        ySet.add(M);

        for (Fence f : fences) {
            xSet.add(f.x1);
            xSet.add(f.x2);

            ySet.add(f.y1);
            ySet.add(f.y2);
        }

        long[] xs = new long[xSet.size()];
        long[] ys = new long[ySet.size()];

        int idx = 0;
        for (long x : xSet)
            xs[idx++] = x;

        idx = 0;
        for (long y : ySet)
            ys[idx++] = y;

        int X = xs.length;
        int Y = ys.length;

        /*
         * Cells:
         *
         * i = 0 ... X-2
         * j = 0 ... Y-2
         */
        int cols = X - 1;
        int rows = Y - 1;

        int cells = cols * rows;

        DSU dsu = new DSU(cells);

        /*
         * Convert cell (i,j) into DSU id.
         */
        // id(i,j) = i * rows + j

        /*
         * Vertical neighbors:
         *
         * cell (i,j)
         * cell (i+1,j)
         *
         * Their common boundary is x = xs[i+1].
         */
        for (int i = 0; i < cols - 1; i++) {

            long x = xs[i + 1];

            for (int j = 0; j < rows; j++) {

                long y1 = ys[j];
                long y2 = ys[j + 1];

                if (!verticalBlocked(x, y1, y2, fences)) {

                    int a = i * rows + j;
                    int b = (i + 1) * rows + j;

                    dsu.union(a, b);
                }
            }
        }

        /*
         * Horizontal neighbors:
         *
         * cell (i,j)
         * cell (i,j+1)
         *
         * Their common boundary is y = ys[j+1].
         */
        for (int j = 0; j < rows - 1; j++) {

            long y = ys[j + 1];

            for (int i = 0; i < cols; i++) {

                long x1 = xs[i];
                long x2 = xs[i + 1];

                if (!horizontalBlocked(y, x1, x2, fences)) {

                    int a = i * rows + j;
                    int b = i * rows + (j + 1);

                    dsu.union(a, b);
                }
            }
        }

        /*
         * Calculate area of every connected component.
         *
         * We only need area modulo MOD because
         * (A^2) mod MOD = ((A mod MOD)^2) mod MOD.
         */
        long[] componentArea = new long[cells];

        for (int i = 0; i < cols; i++) {

            long width = xs[i + 1] - xs[i];

            for (int j = 0; j < rows; j++) {

                long height = ys[j + 1] - ys[j];

                long area =
                        (width % MOD) *
                        (height % MOD) % MOD;

                int id = i * rows + j;
                int root = dsu.find(id);

                componentArea[root] =
                        (componentArea[root] + area) % MOD;
            }
        }

        /*
         * Sum of squares of component areas.
         */
        long numerator = 0;

        for (int i = 0; i < cells; i++) {

            if (dsu.find(i) == i) {

                long area = componentArea[i];

                numerator =
                        (numerator
                                + area * area % MOD)
                                % MOD;
            }
        }

        /*
         * denominator = N * M
         */
        long denominator =
                (N % MOD) * (M % MOD) % MOD;

        /*
         * answer =
         * numerator / denominator
         */
        long inverse =
                modPow(denominator, MOD - 2);

        return numerator * inverse % MOD;
    }

    public static void main(String[] args)
            throws Exception {

        FastScanner fs = new FastScanner();

        int T = fs.nextInt();

        StringBuilder out = new StringBuilder();

        while (T-- > 0) {

            long N = fs.nextLong();
            long M = fs.nextLong();
            int K = fs.nextInt();

            Fence[] fences = new Fence[K];

            for (int i = 0; i < K; i++) {

                long x1 = fs.nextLong();
                long y1 = fs.nextLong();
                long x2 = fs.nextLong();
                long y2 = fs.nextLong();

                fences[i] =
                        new Fence(x1, y1, x2, y2);
            }

            out.append(
                    solve(N, M, fences)
            ).append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {

        private final InputStream in = System.in;

        private final byte[] buffer =
                new byte[1 << 16];

        private int ptr = 0;
        private int len = 0;

        private int read() throws IOException {

            if (ptr >= len) {

                len = in.read(buffer);
                ptr = 0;

                if (len <= 0)
                    return -1;
            }

            return buffer[ptr++];
        }

        long nextLong() throws IOException {

            int c;

            do {
                c = read();
            } while (c <= ' ');

            long sign = 1;

            if (c == '-') {
                sign = -1;
                c = read();
            }

            long result = 0;

            while (c > ' ') {

                result =
                        result * 10
                        + (c - '0');

                c = read();
            }

            return result * sign;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}