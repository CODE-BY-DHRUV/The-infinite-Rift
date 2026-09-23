import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1000000007L;

    static long[] fact;
    static long[] invFact;

    static long modPow(long a, long e) {
        long res = 1;

        while (e > 0) {
            if ((e & 1) == 1) {
                res = res * a % MOD;
            }

            a = a * a % MOD;
            e >>= 1;
        }

        return res;
    }

    static long combination(int n, int r) {
        if (r < 0 || r > n) {
            return 0;
        }

        return fact[n] * invFact[r] % MOD
                * invFact[n - r] % MOD;
    }

    /*
     * Returns the exponent d such that:
     *
     * x = 2^d
     *
     * Returns -1 if x is not a power of 2.
     */
    static int powerOfTwoExponent(long x) {
        if (x <= 0 || (x & (x - 1)) != 0) {
            return -1;
        }

        return Long.numberOfTrailingZeros(x);
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);

        int T = fs.nextInt();

        /*
         * Sum of n <= 5 * 10^5.
         * Precompute factorials once.
         */
        int MAX = 500000;

        fact = new long[MAX + 1];
        invFact = new long[MAX + 1];

        fact[0] = 1;

        for (int i = 1; i <= MAX; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        invFact[MAX] = modPow(fact[MAX], MOD - 2);

        for (int i = MAX; i >= 1; i--) {
            invFact[i - 1] = invFact[i] * i % MOD;
        }

        StringBuilder out = new StringBuilder();

        while (T-- > 0) {

            int n = fs.nextInt();

            long[] a = new long[n];

            long total = 0;

            for (int i = 0; i < n; i++) {
                a[i] = fs.nextLong();
                total += a[i];
            }

            /*
             * Maximum possible depth:
             *
             * total <= 1e14
             * minimum weight >= 1
             *
             * so depth < 50.
             */
            int MAX_DEPTH = 60;

            int[] cnt = new int[MAX_DEPTH];

            boolean possible = true;

            for (long x : a) {

                // total / x must be an integer.
                if (total % x != 0) {
                    possible = false;
                    break;
                }

                long ratio = total / x;

                int depth = powerOfTwoExponent(ratio);

                if (depth == -1 || depth >= MAX_DEPTH) {
                    possible = false;
                    break;
                }

                cnt[depth]++;
            }

            if (!possible) {
                out.append(0).append('\n');
                continue;
            }

            /*
             * At depth 0 there is exactly one node: the root.
             */
            int nodes = 1;

            long answer = 1;

            for (int depth = 0; depth < MAX_DEPTH; depth++) {

                if (cnt[depth] > nodes) {
                    possible = false;
                    break;
                }

                /*
                 * Choose which nodes at this depth are leaves.
                 */
                answer = answer * combination(
                        nodes,
                        cnt[depth]
                ) % MOD;

                /*
                 * All remaining nodes are internal.
                 * Each internal node has exactly 2 children.
                 */
                int internal = nodes - cnt[depth];

                nodes = 2 * internal;

                /*
                 * Once there are no more nodes, we are done.
                 */
                if (nodes == 0) {
                    break;
                }
            }

            /*
             * A valid complete mobile must end with all nodes
             * becoming leaves.
             */
            if (nodes != 0) {
                possible = false;
            }

            out.append(possible ? answer : 0).append('\n');
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

                if (len <= 0) {
                    return -1;
                }
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

            long res = 0;

            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return res * sign;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}