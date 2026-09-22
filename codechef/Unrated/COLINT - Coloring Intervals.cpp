import java.io.*;
import java.util.*;

public class Main {

    static class Interval {
        long l, r;
        int idx;

        Interval(long l, long r, int idx) {
            this.l = l;
            this.r = r;
            this.idx = idx;
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder output = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            int n = fs.nextInt();

            Interval[] arr = new Interval[n];

            for (int i = 0; i < n; i++) {
                long l = fs.nextLong();
                long r = fs.nextLong();
                arr[i] = new Interval(l, r, i);
            }

            // Sort by L increasing.
            // For equal L, R decreasing.
            Arrays.sort(arr, new Comparator<Interval>() {
                @Override
                public int compare(Interval a, Interval b) {
                    if (a.l != b.l) {
                        return Long.compare(a.l, b.l);
                    }
                    return Long.compare(b.r, a.r);
                }
            });

            char[] ans = new char[n];

            int color = 0;
            long maxR = Long.MIN_VALUE;

            for (int i = 0; i < n; i++) {
                Interval cur = arr[i];

                // Assign current color.
                ans[cur.idx] = (char) ('0' + color);

                /*
                 * If the current interval extends farther right
                 * than every previously processed interval,
                 * start the next chain with the opposite color.
                 */
                if (cur.r > maxR) {
                    color ^= 1;
                }

                maxR = Math.max(maxR, cur.r);
            }

            output.append(new String(ans)).append('\n');
        }

        System.out.print(output);
    }

    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        FastScanner(InputStream is) {
            in = is;
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
            } while (c <= ' ');

            boolean neg = false;
            if (c == '-') {
                neg = true;
                c = read();
            }

            long res = 0;
            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return neg ? -res : res;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}