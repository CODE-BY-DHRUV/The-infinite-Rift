
import java.io.*;

public class Main {

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();

        int n = fs.nextInt();

        long[] a = new long[n];

        for (int i = 0; i < n; i++) {
            a[i] = fs.nextLong();
        }

        StringBuilder out = new StringBuilder();

        for (int i = 0; i < n; i++) {

            double expected = 1.0;

            for (int j = 0; j < n; j++) {
                if (i == j) continue;

                expected += (double) a[j] / (a[i] + a[j]);
            }

            if (i > 0) {
                out.append(' ');
            }

            out.append(String.format(java.util.Locale.US, "%.6f", expected));
        }

        System.out.println(out);
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
    }
}
