import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 998244353L;

    // Matrix multiplication
    static long[][] multiply(long[][] a, long[][] b) {

        int n = a.length;
        long[][] c = new long[n][n];

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {

                if (a[i][k] == 0) continue;

                for (int j = 0; j < n; j++) {

                    if (b[k][j] == 0) continue;

                    c[i][j] = (c[i][j]
                            + a[i][k] * b[k][j]) % MOD;
                }
            }
        }

        return c;
    }

    // Matrix exponentiation
    static long[][] power(long[][] a, int exp) {

        int n = a.length;

        long[][] result = new long[n][n];

        for (int i = 0; i < n; i++) {
            result[i][i] = 1;
        }

        while (exp > 0) {

            if ((exp & 1) == 1) {
                result = multiply(result, a);
            }

            a = multiply(a, a);
            exp >>= 1;
        }

        return result;
    }

    static long modPow(long a, long e) {

        long result = 1;

        while (e > 0) {

            if ((e & 1) == 1) {
                result = result * a % MOD;
            }

            a = a * a % MOD;
            e >>= 1;
        }

        return result;
    }

    static long inv(long x) {
        return modPow(x, MOD - 2);
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int N = fs.nextInt();
            int K = fs.nextInt();

            int r = fs.nextInt();
            int c = fs.nextInt();

            /*
             * States:
             *
             * 0 = correct row, correct column
             * 1 = correct row, wrong column
             * 2 = wrong row, correct column
             * 3 = wrong row, wrong column
             */

            long invN = inv(N);
            long inv2N = inv(2L * N);

            long invN2 = invN * invN % MOD;

            /*
             * p = probability of choosing the target row
             * q = probability of choosing the target column
             *
             * Both are 1/(2N).
             */

            long p = inv2N;

            long stay = (1 - 2 * p % MOD
                    + 2 * p % MOD * invN) % MOD;

            if (stay < 0) stay += MOD;

            /*
             * More directly:
             *
             * From A:
             * A -> A = 1 - 1/N + 1/N^2
             * A -> B = (N-1)/(2N^2)
             * A -> C = same
             */
            long aToA =
                    (1 - invN + invN2 + MOD) % MOD;

            long aToB =
                    (inv2N * ((N - 1L) % MOD)) % MOD * invN % MOD;

            long aToC = aToB;

            /*
             * From B:
             *
             * Current position = target row, wrong column.
             *
             * Choosing target row:
             *   -> A with 1/N
             *   -> B with (N-1)/N
             *
             * Choosing current column:
             *   -> B with 1/N
             *   -> D with (N-1)/N
             *
             * All other choices leave it in B.
             */
            long bToA = p * invN % MOD;

            long bToD = p * invN % MOD * (N - 1L) % MOD;

            long bToB =
                    (1 - bToA - bToD + MOD + MOD) % MOD;

            /*
             * By symmetry:
             *
             * C -> A and C -> D
             */
            long cToA = bToA;

            long cToD = bToD;

            long cToC =
                    (1 - cToA - cToD + MOD + MOD) % MOD;

            /*
             * From D:
             *
             * wrong row, wrong column.
             *
             * To become A in one operation is impossible.
             *
             * Selecting target row:
             *   -> C with 1/N
             *
             * Selecting target column:
             *   -> B with 1/N
             */
            long dToB = bToA;
            long dToC = bToA;

            long dToD =
                    (1 - dToB - dToC + MOD + MOD) % MOD;

            long[][] transition = new long[4][4];

            transition[0][0] = aToA;
            transition[0][1] = aToB;
            transition[0][2] = aToC;

            transition[1][0] = bToA;
            transition[1][1] = bToB;
            transition[1][3] = bToD;

            transition[2][0] = cToA;
            transition[2][2] = cToC;
            transition[2][3] = cToD;

            transition[3][1] = dToB;
            transition[3][2] = dToC;
            transition[3][3] = dToD;

            long[][] result = power(transition, K);

            /*
             * Initially we are in state A.
             *
             * Therefore result[0][0] is the probability
             * of being in state A after K operations.
             */
            out.append(result[0][0]).append('\n');
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

            int result = 0;

            while (c > ' ') {
                result = result * 10 + c - '0';
                c = read();
            }

            return result * sign;
        }
    }
}