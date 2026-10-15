import java.io.*;

public class Main {

    static void solve(FastScanner fs, StringBuilder out) throws IOException {
        int n = fs.nextInt();
        long k = fs.nextLong();

        long base = (long) n * (n + 1) / 2 - 1;
        long maxExtra = (long) (n - 1) * (n - 1) / 4;

        if (n == 1) {
            if (k == 0) {
                out.append("1\n");
            } else {
                out.append("-1\n");
            }
            return;
        }

        long extra = k - base;

        if (extra < 0 || extra > maxExtra) {
            out.append("-1\n");
            return;
        }

        int[] ans = new int[n];
        int pos = 0;
        int lo = 1, hi = n;
        int len = n;

        while (len > 0) {
            if (extra == 0) {
                while (lo <= hi) {
                    ans[pos++] = lo++;
                }
                break;
            }

            // Find the smallest suffix length that can achieve extra.
            int suffix = 2;
            while ((long) (suffix - 1) * (suffix - 1) / 4 < extra) {
                suffix++;
            }

            // Keep the prefix in ascending order.
            while (len > suffix) {
                ans[pos++] = lo++;
                len--;
            }

            // Choose the maximum number of outer pairs possible.
            int left = 0, right = (len - 1) / 2;

            while (left < right) {
                int mid = left + (right - left + 1) / 2;
                long gain = (long) mid * (len - mid - 1);

                if (gain <= extra) {
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }

            int pairs = left;
            extra -= (long) pairs * (len - pairs - 1);

            for (int i = 0; i < pairs; i++) {
                ans[pos++] = lo++;
                ans[pos++] = hi--;
            }

            len -= 2 * pairs;
        }

        for (int i = 0; i < n; i++) {
            if (i > 0) out.append(' ');
            out.append(ans[i]);
        }
        out.append('\n');
    }

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();
        while (t-- > 0) {
            solve(fs, out);
        }

        System.out.print(out);
    }

    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr, len;

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

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}