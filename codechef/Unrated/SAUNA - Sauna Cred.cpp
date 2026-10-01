
import java.io.*;
import java.util.*;

public class Main {

    static class Event {
        long x;
        int delta;
        boolean start;

        Event(long x, int delta, boolean start) {
            this.x = x;
            this.delta = delta;
            this.start = start;
        }
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();
            long t = fs.nextLong();

            Event[] events = new Event[2 * n];
            int ec = 0;

            for (int i = 0; i < n; i++) {

                long l = fs.nextLong();
                long r = fs.nextLong();

                long a = r - t;
                long b = l;

                /*
                 * If a < b:
                 *
                 *   contribution = +1 on (a, b)
                 *
                 * If b < a:
                 *
                 *   contribution = -1 on (b, a)
                 *
                 * If equal:
                 *
                 *   contribution = 0 everywhere.
                 */

                if (a < b) {

                    // Start +1 interval at a
                    events[ec++] = new Event(a, +1, true);

                    // End +1 interval at b
                    events[ec++] = new Event(b, -1, false);

                } else if (b < a) {

                    // Start -1 interval at b
                    events[ec++] = new Event(b, -1, true);

                    // End -1 interval at a
                    events[ec++] = new Event(a, +1, false);
                }
            }

            Arrays.sort(events, 0, ec, (e1, e2) ->
                    Long.compare(e1.x, e2.x));

            int cur = 0;
            int answer = 0;

            int i = 0;

            while (i < ec) {

                long x = events[i].x;

                /*
                 * At exactly x, all open intervals ending at x
                 * are already excluded, and all intervals starting
                 * at x are also excluded.
                 *
                 * Therefore:
                 *
                 * 1. Apply all END events.
                 * 2. cur is the value exactly at x.
                 * 3. Apply all START events.
                 * 4. cur is the value immediately to the right of x.
                 */

                int j = i;

                // First process all END events at x.
                while (j < ec && events[j].x == x) {
                    if (!events[j].start) {
                        cur += events[j].delta;
                    }
                    j++;
                }

                // Value at x itself.
                answer = Math.max(answer, cur);

                // Then process all START events at x.
                j = i;

                while (j < ec && events[j].x == x) {
                    if (events[j].start) {
                        cur += events[j].delta;
                    }
                    j++;
                }

                // Value immediately after x.
                answer = Math.max(answer, cur);

                i = j;
            }

            out.append(answer).append('\n');
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
}



