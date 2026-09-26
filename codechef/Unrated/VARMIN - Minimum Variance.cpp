import java.io.*;
import java.util.*;

public class Main {

    static class Event implements Comparable<Event> {
        int pos;       // 2 * midpoint = a + b
        int setId;
        int newValue;

        Event(int pos, int setId, int newValue) {
            this.pos = pos;
            this.setId = setId;
            this.newValue = newValue;
        }

        @Override
        public int compareTo(Event other) {
            return Integer.compare(this.pos, other.pos);
        }
    }

    static long boundaryValue(long n, long sum, long sumSq, long t) {
        /*
         * Here:
         *      mu = t / 2
         *
         * We need:
         *
         * n * F(mu)
         * = n * [sumSq - 2*sum*mu + n*mu^2]
         *
         * Avoid fractions by using:
         *
         * 4 * F(mu)
         * = 4*sumSq - 4*sum*t + n*t^2
         *
         * Therefore:
         *
         * n * F(mu)
         * = n * (4*sumSq - 4*sum*t + n*t^2) / 4
         */

        long fourF =
                4L * sumSq
                - 4L * sum * t
                + n * t * t;

        // Compute n * fourF / 4 without overflow.
        if (fourF % 4 == 0) {
            return (fourF / 4) * n;
        }

        if (n % 4 == 0) {
            return (n / 4) * fourF;
        }

        if (n % 2 == 0 && fourF % 2 == 0) {
            return (n / 2) * (fourF / 2);
        }

        // This case is theoretically unnecessary if the arithmetic
        // divisibility is considered, but keep it safe.
        return (n * fourF) / 4;
    }

    static long solve(int n, int[][] sets) {

        int[] current = new int[n];

        long sum = 0;
        long sumSq = 0;

        ArrayList<Event> events = new ArrayList<>();

        /*
         * Initially mu is very small, so from every set we choose
         * its smallest element.
         *
         * For consecutive values a < b, the chosen value changes
         * from a to b at:
         *
         *       mu = (a + b) / 2
         *
         * We store 2*mu = a+b.
         */
        for (int i = 0; i < n; i++) {
            int[] a = sets[i];
            Arrays.sort(a);

            current[i] = a[0];

            sum += a[0];
            sumSq += (long) a[0] * a[0];

            for (int j = 0; j + 1 < a.length; j++) {
                int midpointTwice = a[j] + a[j + 1];

                events.add(
                    new Event(midpointTwice, i, a[j + 1])
                );
            }
        }

        Collections.sort(events);

        long answer = Long.MAX_VALUE;

        /*
         * We work with t = 2*mu.
         *
         * Between two consecutive events, every set chooses a fixed
         * value. Therefore:
         *
         * F(mu) = sumSq - 2*sum*mu + n*mu^2
         *
         * Its minimum is at:
         *
         * mu = sum / n
         *
         * if that point lies inside the current interval.
         */

        long left = 0;

        int idx = 0;

        while (idx < events.size()) {

            int right = events.get(idx).pos;

            // Check the quadratic minimum inside [left, right].
            //
            // Candidate t = 2*sum/n.
            if (2L * sum >= (long) n * left &&
                2L * sum <= (long) n * right) {

                long candidate =
                        (long) n * sumSq - sum * sum;

                answer = Math.min(answer, candidate);
            }

            /*
             * The endpoint right itself is also important.
             * The optimum can occur exactly at a midpoint.
             */
            long boundary = boundaryValue(
                    n, sum, sumSq, right
            );

            answer = Math.min(answer, boundary);

            /*
             * Process all sets whose nearest value changes at
             * this same midpoint.
             */
            while (idx < events.size()
                    && events.get(idx).pos == right) {

                Event e = events.get(idx);

                int old = current[e.setId];
                int neu = e.newValue;

                sum += (long) neu - old;
                sumSq +=
                        (long) neu * neu
                        - (long) old * old;

                current[e.setId] = neu;

                idx++;
            }

            left = right;
        }

        /*
         * Last interval after the final breakpoint.
         * There is no upper breakpoint, but all possible means are
         * between 1 and 50000, so using a sufficiently large endpoint
         * is enough.
         */
        long right = 100000;

        if (2L * sum >= (long) n * left &&
            2L * sum <= (long) n * right) {

            long candidate =
                    (long) n * sumSq - sum * sum;

            answer = Math.min(answer, candidate);
        }

        return answer;
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);

        int n = fs.nextInt();

        int[][] sets = new int[n][];

        for (int i = 0; i < n; i++) {

            int m = fs.nextInt();

            sets[i] = new int[m];

            for (int j = 0; j < m; j++) {
                sets[i][j] = fs.nextInt();
            }
        }

        System.out.println(solve(n, sets));
    }

    // Fast input for Java 8
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

            int res = 0;

            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return res * sign;
        }
    }
}