import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;
    static final int MAX = 2500;

    static long[][] dp;
    static long[] inv;

    static long modPow(long a, int e) {
        long res = 1;

        while (e > 0) {
            if ((e & 1) != 0)
                res = res * a % MOD;

            a = a * a % MOD;
            e >>= 1;
        }

        return res;
    }

    static long intervals(int m) {
        return (long) m * (m + 1) / 2;
    }

    static void precompute() {

        dp = new long[MAX + 1][];

        /*
         * Because n * m <= 2500, for a fixed n we only
         * need m <= 2500 / n.
         */
        for (int n = 1; n <= MAX; n++) {
            dp[n] = new long[MAX / n + 1];
        }

        /*
         * Modular inverses, needed for computing C(n,l).
         */
        inv = new long[MAX + 1];

        inv[1] = 1;

        for (int i = 2; i <= MAX; i++) {
            inv[i] = MOD - (MOD / i) * inv[(int) (MOD % i)] % MOD;
        }

        /*
         * Compute states in increasing n.
         *
         * For fixed n, compute increasing m.
         */
        for (int n = 1; n <= MAX; n++) {

            int maxM = MAX / n;

            /*
             * C(n,l)
             */
            long[] comb = new long[n + 1];

            comb[0] = 1;

            for (int l = 1; l <= n; l++) {
                comb[l] = comb[l - 1]
                        * (n - l + 1) % MOD
                        * inv[l] % MOD;
            }

            for (int m = 1; m <= maxM; m++) {

                long total = modPow(intervals(m) % MOD, n);

                /*
                 * Graphs in which the last right vertex
                 * is isolated.
                 */
                long isolated = modPow(
                        intervals(m - 1) % MOD,
                        n
                );

                long ans = (total - isolated + MOD) % MOD;

                /*
                 * Subtract disconnected graphs.
                 *
                 * k = number of right vertices in the
                 * component containing vertex m.
                 *
                 * k < m, because k == m together with
                 * l == n would be the complete graph itself,
                 * causing circular dependency.
                 *
                 * For k == m and l < n, the remaining left
                 * vertices would have zero available right
                 * vertices, which is not allowed.
                 */
                for (int k = 1; k < m; k++) {

                    long base = intervals(m - k) % MOD;

                    /*
                     * We iterate l from n down to 1.
                     *
                     * exponent = n-l
                     *
                     * At l=n:
                     * exponent = 0 -> power = 1
                     *
                     * After moving to l=n-1:
                     * exponent = 1
                     *
                     * Thus we avoid doing a pow() inside
                     * the O(n*m) transition.
                     */
                    long power = 1;

                    for (int l = n; l >= 1; l--) {

                        long ways = dp[l][k];

                        long term = comb[l] * ways % MOD;
                        term = term * power % MOD;

                        ans -= term;

                        if (ans < 0)
                            ans += MOD;

                        power = power * base % MOD;
                    }
                }

                dp[n][m] = ans;
            }
        }
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();

        precompute();

        int T = fs.nextInt();

        StringBuilder out = new StringBuilder();

        while (T-- > 0) {

            int n = fs.nextInt();
            int m = fs.nextInt();

            out.append(dp[n][m]).append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {

        private final InputStream in = System.in;

        private final byte[] buffer = new byte[1 << 16];

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