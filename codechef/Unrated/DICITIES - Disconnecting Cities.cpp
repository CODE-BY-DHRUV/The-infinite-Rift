
import java.io.*;
import java.util.*;

public class Main {

    static final long INF = Long.MAX_VALUE / 4;

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            int n = fs.nextInt();
            int k = fs.nextInt();

            long[][] w = new long[n][n];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    w[i][j] = fs.nextLong();
                }
            }

            int r = n - k;              // number of non-special cities
            int totalMasks = 1 << r;
            int allMask = totalMasks - 1;

            // Special cities: 0 ... k-1
            // Non-special cities: k ... n-1

            // degree[v] = sum of all roads incident to v
            long[] degree = new long[n];

            for (int i = 0; i < n; i++) {
                long sum = 0;
                for (int j = 0; j < n; j++) {
                    sum += w[i][j];
                }
                degree[i] = sum;
            }

            /*
             * sumDegree[mask] =
             * sum of degrees of non-special vertices in mask.
             */
            long[] sumDegree = new long[totalMasks];

            /*
             * internal[mask] =
             * total weight of roads whose two endpoints are
             * non-special vertices belonging to mask.
             */
            long[] internal = new long[totalMasks];

            for (int mask = 1; mask < totalMasks; mask++) {
                int bit = mask & -mask;
                int pos = Integer.numberOfTrailingZeros(bit);
                int prev = mask ^ bit;

                int vertex = k + pos;

                sumDegree[mask] = sumDegree[prev] + degree[vertex];

                long add = 0;
                int x = prev;

                while (x != 0) {
                    int b = x & -x;
                    int p = Integer.numberOfTrailingZeros(b);

                    add += w[vertex][k + p];

                    x ^= b;
                }

                internal[mask] = internal[prev] + add;
            }

            /*
             * cutCost[i][mask]:
             *
             * group consists of special city i plus all
             * non-special cities contained in mask.
             *
             * cut(G) = sum(degrees of vertices in G)
             *           - 2 * (sum of internal edge weights in G)
             */
            long[][] cutCost = new long[k][totalMasks];

            for (int i = 0; i < k; i++) {
                for (int mask = 0; mask < totalMasks; mask++) {

                    long degreeSum = degree[i] + sumDegree[mask];

                    // Internal edges among non-special cities.
                    long inside = internal[mask];

                    // Edges from special city i to non-special vertices.
                    int x = mask;

                    while (x != 0) {
                        int bit = x & -x;
                        int pos = Integer.numberOfTrailingZeros(bit);

                        inside += w[i][k + pos];

                        x ^= bit;
                    }

                    cutCost[i][mask] = degreeSum - 2L * inside;
                }
            }

            /*
             * dp[mask]:
             * minimum sum of cutCost for the special cities
             * processed so far.
             */
            long[] dp = new long[totalMasks];
            Arrays.fill(dp, INF);
            dp[0] = 0;

            /*
             * Process first k-1 special cities.
             *
             * For each mask, choose 'sub' as the non-special
             * vertices assigned to the current special city.
             */
            for (int special = 0; special < k - 1; special++) {

                long[] next = new long[totalMasks];
                Arrays.fill(next, INF);

                for (int mask = 0; mask < totalMasks; mask++) {

                    /*
                     * Enumerate all submasks of mask.
                     *
                     * The remaining vertices (mask ^ sub)
                     * were assigned to previous special cities.
                     */
                    int sub = mask;

                    while (true) {
                        long previous = dp[mask ^ sub];

                        if (previous != INF) {
                            long value = previous + cutCost[special][sub];

                            if (value < next[mask]) {
                                next[mask] = value;
                            }
                        }

                        if (sub == 0) {
                            break;
                        }

                        sub = (sub - 1) & mask;
                    }
                }

                dp = next;
            }

            /*
             * The last special city gets every non-special
             * city that hasn't already been assigned.
             */
            long best = INF;

            for (int mask = 0; mask < totalMasks; mask++) {
                int remaining = allMask ^ mask;

                long value = dp[mask] + cutCost[k - 1][remaining];

                if (value < best) {
                    best = value;
                }
            }

            /*
             * Every destroyed road was counted twice.
             */
            long answer = best / 2;

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }

    // Fast input
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        FastScanner(InputStream is) {
            in = is;
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
            return (int) nextLong();
        }

        long nextLong() throws IOException {
            int c;

            do {
                c = read();
            } while (c <= ' ');

            boolean negative = false;

            if (c == '-') {
                negative = true;
                c = read();
            }

            long res = 0;

            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return negative ? -res : res;
        }
    }
}
