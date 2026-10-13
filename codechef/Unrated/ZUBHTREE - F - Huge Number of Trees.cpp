
import java.io.*;
import java.util.*;

public class Main {
    static final long MOD = 1_000_000_007L;
    static final int MAX = 500;

    static long[] fact = new long[MAX + 1];
    static long[] invFact = new long[MAX + 1];
    static long[] inv = new long[MAX + 1];

    static long modPow(long a, long e) {
        long r = 1;
        while (e > 0) {
            if ((e & 1) != 0) r = r * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return r;
    }

    static void initMath() {
        fact[0] = 1;
        for (int i = 1; i <= MAX; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        invFact[MAX] = modPow(fact[MAX], MOD - 2);
        for (int i = MAX; i >= 1; i--) {
            invFact[i - 1] = invFact[i] * i % MOD;
        }

        for (int i = 1; i <= MAX; i++) {
            inv[i] = modPow(i, MOD - 2);
        }
    }

    /*
     * w[p][m] = coefficient of x^m in
     * (sum_{j >= k} x^j / j!)^p
     */
    static long[][] buildW(int k, int limit) {
        long[][] w = new long[limit + 1][limit + 1];
        w[0][0] = 1;

        long factor = invFact[k - 1];

        for (int p = 1; p <= limit; p++) {
            for (int m = 1; m <= limit; m++) {
                long value = w[p][m - 1];

                if (m >= k) {
                    value += factor * w[p - 1][m - k] % MOD;
                    if (value >= MOD) value -= MOD;
                }

                w[p][m] = (long) p * value % MOD * inv[m] % MOD;
            }
        }

        return w;
    }

    static long[] calculate(int d, int limit) {
        int k = d - 1;
        long[][] w = buildW(k, limit);

        // dp[used][last] represents normalized counts of level sequences.
        long[][] dp = new long[limit + 1][limit + 1];

        // The root has at least d children.
        for (int first = d; first <= limit; first++) {
            dp[first][first] = invFact[first];
        }

        for (int used = 1; used <= limit; used++) {
            for (int p = 1; p <= used; p++) {
                long cur = dp[used][p];
                if (cur == 0) continue;

                // Each of the p parents must have at least k children.
                int minNext = k * p;
                int maxNext = limit - used;

                for (int m = minNext; m <= maxNext; m++) {
                    long ways = w[p][m];
                    if (ways == 0) continue;

                    long add = cur * ways % MOD;
                    dp[used + m][m] += add;

                    if (dp[used + m][m] >= MOD) {
                        dp[used + m][m] -= MOD;
                    }
                }
            }
        }

        long[] answer = new long[limit + 1];

        for (int n = 2; n <= limit; n++) {
            long total = 0;

            for (int last = 1; last <= n; last++) {
                total += dp[n][last];
                if (total >= MOD) total -= MOD;
            }

            answer[n] = total * fact[n] % MOD;
        }

        return answer;
    }

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner();

        int T = fs.nextInt();
        int[] n = new int[T];
        int[] d = new int[T];
        int[] maxN = new int[11];

        for (int i = 0; i < T; i++) {
            n[i] = fs.nextInt();
            d[i] = fs.nextInt();
            maxN[d[i]] = Math.max(maxN[d[i]], n[i]);
        }

        initMath();

        long[][] answers = new long[11][];

        for (int degree = 2; degree <= 10; degree++) {
            if (maxN[degree] > 0) {
                answers[degree] =
                    calculate(degree, maxN[degree]);
            }
        }

        StringBuilder out = new StringBuilder();

        for (int i = 0; i < T; i++) {
            out.append("Case ").append(i + 1).append(": ")
               .append(answers[d[i]][n[i]]).append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr, len;

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
            } while (c <= ' ' && c != -1);

            int value = 0;
            while (c > ' ') {
                value = value * 10 + c - '0';
                c = read();
            }
            return value;
        }
    }
}

