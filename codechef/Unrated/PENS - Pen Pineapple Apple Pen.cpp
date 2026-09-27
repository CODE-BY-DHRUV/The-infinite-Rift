import java.io.*;
import java.util.*;

public class Main {

    static final int ALPHA = 20;
    static final int SIZE = 1 << ALPHA;

    /*
     * best[mask] = pen number that can write every character
     * represented by mask.
     *
     * If best[mask] == 0, no such pen exists.
     */
    static int[] best;

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder output = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int N = fs.nextInt();
            int K = fs.nextInt();

            String S = fs.next();

            best = new int[SIZE];

            // Store one pen for each exact mask.
            for (int pen = 1; pen <= K; pen++) {

                String p = fs.next();

                int mask = 0;

                for (int j = 0; j < p.length(); j++) {
                    mask |= 1 << (p.charAt(j) - 'a');
                }

                // Any pen with this exact mask is sufficient.
                if (best[mask] == 0) {
                    best[mask] = pen;
                }
            }

            /*
             * SOS DP:
             *
             * After this, best[mask] contains a pen whose
             * capabilities are a SUPERSET of mask.
             */
            for (int bit = 0; bit < ALPHA; bit++) {

                int step = 1 << bit;

                for (int mask = 0; mask < SIZE; mask++) {

                    if ((mask & step) != 0) {
                        continue;
                    }

                    if (best[mask] == 0) {
                        best[mask] = best[mask | step];
                    }
                }
            }

            int[] answer = new int[N];

            int i = 0;

            while (i < N) {

                int mask = 0;
                int j = i;

                /*
                 * Find the longest prefix starting at i
                 * that can be written by one pen.
                 */
                while (j < N) {

                    int bit = 1 << (S.charAt(j) - 'a');

                    int newMask = mask | bit;

                    if (best[newMask] == 0) {
                        break;
                    }

                    mask = newMask;
                    j++;
                }

                /*
                 * A solution is guaranteed to exist, so
                 * at least S[i] can be written.
                 */
                int pen = best[mask];

                for (int k = i; k < j; k++) {
                    answer[k] = pen;
                }

                i = j;
            }

            for (i = 0; i < N; i++) {
                if (i > 0) {
                    output.append(' ');
                }

                output.append(answer[i]);
            }

            output.append('\n');
        }

        System.out.print(output);
    }

    // Fast input for large constraints
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

        String next() throws IOException {

            StringBuilder sb = new StringBuilder();

            int c;

            do {
                c = read();
            } while (c <= ' ');

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }

            return sb.toString();
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

            int result = 0;

            while (c > ' ') {
                result = result * 10 + (c - '0');
                c = read();
            }

            return result * sign;
        }
    }
}