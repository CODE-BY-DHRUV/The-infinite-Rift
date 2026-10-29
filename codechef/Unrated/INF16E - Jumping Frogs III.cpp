
import java.io.*;
import java.util.Arrays;

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

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);

            long sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            long value = 0;
            while (c > ' ') {
                value = value * 10 + c - '0';
                c = read();
            }
            return value * sign;
        }
    }

    // ceil(a / b), where b > 0
    static long ceilDiv(long a, long b) {
        return -Math.floorDiv(-a, b);
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int T = (int) fs.nextLong();

        for (int tc = 1; tc <= T; tc++) {
            int R = (int) fs.nextLong();
            int G = (int) fs.nextLong();

            long A = fs.nextLong();
            long B = fs.nextLong();

            int total = R + G;
            long[] events = new long[2 * total];
            int eventCount = 0;
            long permanent = 0;

            for (int i = 0; i < total; i++) {
                long P = fs.nextLong();
                long V = fs.nextLong();

                boolean red = i < R;

                if (V == 0) {
                    if (A <= P && P <= B) {
                        permanent++;
                    }
                    continue;
                }

                long start, end;

                if (red) {
                    // A <= P + V*t <= B
                    start = ceilDiv(A - P, V);
                    end = Math.floorDiv(B - P, V);
                } else {
                    // A <= P - V*t <= B
                    start = ceilDiv(P - B, V);
                    end = Math.floorDiv(P - A, V);
                }

                start = Math.max(start, 0);

                if (start > end) {
                    continue;
                }

                // Encode events:
                // even = +1 at start
                // odd  = -1 at end + 1
                events[eventCount++] = start * 2;
                events[eventCount++] = (end + 1) * 2 + 1;
            }

            Arrays.sort(events, 0, eventCount);

            long current = permanent;
            long answer = permanent;

            int i = 0;

            while (i < eventCount) {
                long time = events[i] / 2;
                long change = 0;

                // Process all events at the same time together.
                while (i < eventCount && events[i] / 2 == time) {
                    if ((events[i] & 1L) == 0) {
                        change++;
                    } else {
                        change--;
                    }
                    i++;
                }

                current += change;
                answer = Math.max(answer, current);
            }

            out.append("Case ")
               .append(tc)
               .append(": ")
               .append(answer)
               .append('\n');
        }

        System.out.print(out);
    }
}

