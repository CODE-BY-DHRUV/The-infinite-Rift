
import java.io.*;
import java.util.Arrays;

public class Main {
    static final int MOD = 663224321;
    static final int ROOT = 3;

    static long modPow(long a, long e) {
        long result = 1;
        while (e > 0) {
            if ((e & 1) != 0) result = result * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return result;
    }

    static void ntt(int[] a, boolean invert) {
        int n = a.length;

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
            long wlen = modPow(ROOT, (MOD - 1L) / len);
            if (invert) wlen = modPow(wlen, MOD - 2L);

            int half = len >> 1;

            for (int i = 0; i < n; i += len) {
                long w = 1;

                for (int j = 0; j < half; j++) {
                    int u = a[i + j];
                    int v = (int) (a[i + j + half] * w % MOD);

                    long sum = (long) u + v;
                    if (sum >= MOD) sum -= MOD;

                    long diff = (long) u - v;
                    if (diff < 0) diff += MOD;

                    a[i + j] = (int) sum;
                    a[i + j + half] = (int) diff;

                    w = w * wlen % MOD;
                }
            }
        }

        if (invert) {
            long invN = modPow(n, MOD - 2L);
            for (int i = 0; i < n; i++) {
                a[i] = (int) (a[i] * invN % MOD);
            }
        }
    }

    static int[] multiply(int[] a, int[] b) {
        int resultLength = a.length + b.length - 1;
        int size = 1;

        while (size < resultLength) size <<= 1;

        int[] fa = Arrays.copyOf(a, size);
        int[] fb = Arrays.copyOf(b, size);

        ntt(fa, false);
        ntt(fb, false);

        for (int i = 0; i < size; i++) {
            fa[i] = (int) ((long) fa[i] * fb[i] % MOD);
        }

        ntt(fa, true);
        return Arrays.copyOf(fa, resultLength);
    }

    // Computes the inverse of polynomial q modulo x^n.
    // Requires q[0] = 1.
    static int[] inversePolynomial(int[] q, int n) {
        int[] inv = {1};

        while (inv.length < n) {
            int m = Math.min(inv.length * 2, n);

            int[] qPart = Arrays.copyOf(q, m);
            int[] product = multiply(qPart, inv);

            // h = 2 - q * inv (mod x^m)
            int[] h = new int[m];

            h[0] = product[0] == 0
                    ? 2
                    : (int) ((2L - product[0] + MOD) % MOD);

            for (int i = 1; i < m; i++) {
                h[i] = (i < product.length && product[i] != 0)
                        ? MOD - product[i] : 0;
            }

            // inv_new = inv * h (mod x^m)
            int[] next = multiply(inv, h);
            inv = Arrays.copyOf(next, m);
        }

        return inv;
    }

    public static void main(String[] args) throws Exception {
        BufferedInputStream in =
                new BufferedInputStream(System.in);
        StringBuilder out = new StringBuilder();

        int t = nextInt(in);
        int[] queries = new int[t];
        int maxN = 0;

        for (int i = 0; i < t; i++) {
            queries[i] = nextInt(in);
            maxN = Math.max(maxN, queries[i]);
        }

        // Use a power-of-two polynomial length.
        int size = 1;
        while (size <= maxN) size <<= 1;

        // Q(x) = 1 - x * A(x)
        // A(x) = sum(m^(m-1) * x^m), with a[0] = 1.
        int[] q = new int[size];
        q[0] = 1;
        q[1] = MOD - 1;

        for (int i = 2; i < size; i++) {
            int m = i - 1;
            long rootedTrees = modPow(m, m - 1L);
            q[i] = rootedTrees == 0
                    ? 0 : (int) (MOD - rootedTrees);
        }

        // D(x) = 1 / Q(x); its coefficients are dp[n].
        int[] dp = inversePolynomial(q, size);

        for (int n : queries) {
            out.append(dp[n]).append('\n');
        }

        System.out.print(out);
    }

    static int nextInt(BufferedInputStream in) throws IOException {
        int c;
        do {
            c = in.read();
        } while (c <= ' ' && c != -1);

        int value = 0;
        while (c > ' ') {
            value = value * 10 + c - '0';
            c = in.read();
        }
        return value;
    }
}
