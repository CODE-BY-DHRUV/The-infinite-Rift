import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            int n = fs.nextInt();

            long[] a = new long[n];

            for (int i = 0; i < n; i++) {
                a[i] = fs.nextLong();
            }

            double[][] alice = new double[n][n];
            double[][] bob = new double[n][n];

            // Base case: only one candy remains.
            for (int i = 0; i < n; i++) {
                alice[i][i] = a[i];
                bob[i][i] = 0.0;
            }

            // Length of interval
            for (int len = 2; len <= n; len++) {

                for (int l = 0; l + len - 1 < n; l++) {

                    int r = l + len - 1;

                    // Alice picks left or right.
                    alice[l][r] =
                            (a[l] + bob[l + 1][r]
                           + a[r] + bob[l][r - 1]) / 2.0;

                    // Bob picks left or right.
                    bob[l][r] =
                            (alice[l + 1][r]
                           + alice[l][r - 1]) / 2.0;
                }
            }

            out.append(String.format(Locale.US,
                    "%.15f\n", alice[0][n - 1]));
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

            boolean negative = false;

            if (c == '-') {
                negative = true;
                c = read();
            }

            long result = 0;

            while (c > ' ') {
                result = result * 10 + (c - '0');
                c = read();
            }

            return negative ? -result : result;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}