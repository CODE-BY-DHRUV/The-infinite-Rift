
import java.io.*;

public class Main {
    static final long MOD = 1_000_000_007L;

    static long[][] multiply(long[][] A, long[][] B) {
        int n = A.length;
        int m = B[0].length;
        int p = B.length;
        long[][] C = new long[n][m];

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < p; k++) {
                if (A[i][k] == 0) continue;
                long v = A[i][k];
                for (int j = 0; j < m; j++) {
                    C[i][j] = (C[i][j] + v * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    static long[][] power(long[][] A, long exp) {
        int n = A.length;
        long[][] result = new long[n][n];

        for (int i = 0; i < n; i++) result[i][i] = 1;

        while (exp > 0) {
            if ((exp & 1) == 1) result = multiply(result, A);
            A = multiply(A, A);
            exp >>= 1;
        }
        return result;
    }

    static long modPow(long a, long exp) {
        long result = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) result = result * a % MOD;
            a = a * a % MOD;
            exp >>= 1;
        }
        return result;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);

        long N = fs.nextLong();
        int K = (int) fs.nextLong();
        int a = (int) fs.nextLong();
        int b = (int) fs.nextLong();

        int s = K / 2 - 1;

        long[][] M = new long[K][K];

        for (int i = 0; i < K; i++) {
            for (int j = Math.max(0, i - 1);
                 j <= Math.min(K - 1, i + 1); j++) {
                M[i][j] = 1;
            }
        }

        // Allowed obstacle heights: a+1 through b-1 (1-based).
        long[][] D = new long[K][K];
        for (int y = a; y < b - 1; y++) {
            D[y][y] = 1;
        }

        int size = 2 * K;
        long[][] B = new long[size][size];

        // B = [[M, D],
        //      [0, M]]
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < K; j++) {
                B[i][j] = M[i][j];
                B[i][j + K] = D[i][j];
                B[i + K][j + K] = M[i][j];
            }
        }

        // Sum contributions for obstacle positions x = 1 through N.
        long[][] result = power(B, N);
        long total = result[s][s + K];

        // Remove the two invalid endpoint positions x = 1 and x = N.
        long[][] MN = power(M, N - 1);
        long endpoint = D[s][s] * MN[s][s] % MOD;

        total = (total - 2 * endpoint % MOD + MOD) % MOD;

        // There are N-2 possible obstacle positions.
        long answer = total * modPow(N - 2, MOD - 2) % MOD;
        System.out.println(answer);
    }

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

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);

            long value = 0;
            while (c > ' ') {
                value = value * 10 + c - '0';
                c = read();
            }
            return value;
        }
    }
}
