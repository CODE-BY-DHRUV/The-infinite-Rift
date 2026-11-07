
import java.io.*;
import java.util.*;

public class Main {

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

        String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int c;

            do {
                c = read();
            } while (c <= 32 && c != -1);

            while (c > 32) {
                sb.append((char) c);
                c = read();
            }

            return sb.toString();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        long nextLong() throws IOException {
            return Long.parseLong(next());
        }
    }

    static long[] calculate(String a, long mod) {

        int n = a.length();

        long[] prefix = new long[n + 1];

        // Prefix values modulo mod
        for (int i = 0; i < n; i++) {
            int digit = a.charAt(i) - '0';

            prefix[i + 1] =
                (prefix[i] * 10 + digit) % mod;
        }

        long[] S = new long[10];

        long low = 0;
        long pow = 1;

        // Process digit positions from right to left
        for (int i = n - 1; i >= 0; i--) {

            int cur = a.charAt(i) - '0';

            long high = prefix[i];

            long pow2 = (pow * pow) % mod;

            for (int d = 1; d <= 9; d++) {

                // Contribution from complete cycles
                long term1 = (high + (cur > d ? 1 : 0)) % mod;

                term1 = (term1 * pow2) % mod;

                // Contribution when current digit equals d
                long term2 = 0;

                if (cur == d) {
                    term2 = ((low + 1) % mod * pow) % mod;
                }

                S[d] = (S[d] + term1 + term2) % mod;
            }

            // Update suffix value
            low = (cur * pow + low) % mod;

            // Update power of 10
            pow = (pow * 10) % mod;
        }

        return S;
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int[][] M = new int[10][10];

        // Read multiplication matrix
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                M[i][j] = fs.nextInt();
            }
        }

        int T = fs.nextInt();

        while (T-- > 0) {

            String A = fs.next();
            long mod = fs.nextLong();

            long[] S = calculate(A, mod);

            long ans = 0;

            // Calculate sum over all ordered pairs
            for (int i = 1; i <= 9; i++) {

                for (int j = 1; j <= 9; j++) {

                    long contribution =
                        (M[i][j] * S[i]) % mod;

                    contribution =
                        (contribution * S[j]) % mod;

                    ans = (ans + contribution) % mod;
                }
            }

            out.append(ans).append('\n');
        }

        System.out.print(out);
    }
}

