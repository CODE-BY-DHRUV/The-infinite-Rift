import java.io.*;
import java.util.*;

public class Main {

    // Fast input for large Q
    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

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

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();

            /*
             * Maximum possible number of generated elements
             * is small enough:
             *
             * n <= 1000
             * values <= 1000
             *
             * At most about n * 1000 generated values are needed.
             */
            int MAX = n * 1005 + n + 10;

            long[] a = new long[MAX];

            for (int i = 0; i < n; i++) {
                a[i] = fs.nextLong();
            }

            int len = n;

            /*
             * Generate until the last n elements are equal.
             */
            while (true) {

                boolean same = true;

                long value = a[len - 1];

                for (int i = len - n; i < len; i++) {
                    if (a[i] != value) {
                        same = false;
                        break;
                    }
                }

                if (same) {
                    break;
                }

                /*
                 * Sliding-window sum.
                 *
                 * Since n <= 1000, we could calculate the sum
                 * directly, but maintaining it is cleaner and faster.
                 */
                long sum = 0;

                for (int i = len - n; i < len; i++) {
                    sum += a[i];
                }

                a[len] = sum / n;
                len++;
            }

            /*
             * The sequence is constant from position:
             *
             * (len - n + 1)
             *
             * onward.
             *
             * Example:
             * n = 3
             * sequence = 2 2 3 2 2 2 2 ...
             *
             * if len = 6, the last window is positions 4..6,
             * so positions 4 onward are permanently 2.
             */
            int stableStart = len - n;

            int Q = fs.nextInt();

            while (Q-- > 0) {

                long x = fs.nextLong();

                if (x <= len) {
                    // x is inside the explicitly generated part
                    out.append(a[(int) x - 1]).append('\n');
                } else {
                    // All elements after len are equal to a[len-1]
                    out.append(a[len - 1]).append('\n');
                }
            }
        }

        System.out.print(out);
    }
}
