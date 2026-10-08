
import java.io.*;

public class Main {

    static final int K = 7;
    static final int MASKS = 1 << K;

    static int getId(int x) {
        if (x == 10) return 0;
        if (x == 20) return 1;
        if (x == 50) return 2;
        if (x == 100) return 3;
        if (x == 200) return 4;
        if (x == 500) return 5;
        return 6; // 2000
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();

            // dp[mask * 7 + last]
            int[] dp = new int[MASKS * K];

            // best[mask] = maximum length for this mask
            int[] best = new int[MASKS];

            for (int i = 0; i < n; i++) {

                int denomination = fs.nextInt();

                // IMPORTANT:
                // Convert 10,20,50,... into 0,1,2,...,6.
                int x = getId(denomination);

                int bit = 1 << x;

                /*
                 * Case 1:
                 * x is already the last block.
                 *
                 * We can keep this note and extend that block.
                 */
                for (int mask = 0; mask < MASKS; mask++) {

                    if ((mask & bit) != 0) {

                        int idx = mask * K + x;

                        if (dp[idx] > 0) {
                            dp[idx]++;

                            if (dp[idx] > best[mask]) {
                                best[mask] = dp[idx];
                            }
                        }
                    }
                }

                /*
                 * Case 2:
                 * Start a NEW block containing denomination x.
                 *
                 * x must not have appeared in an earlier block.
                 */
                for (int mask = 0; mask < MASKS; mask++) {

                    if ((mask & bit) == 0) {

                        int newMask = mask | bit;
                        int newLength = best[mask] + 1;

                        int idx = newMask * K + x;

                        if (newLength > dp[idx]) {
                            dp[idx] = newLength;

                            if (newLength > best[newMask]) {
                                best[newMask] = newLength;
                            }
                        }
                    }
                }
            }

            int keep = 0;

            for (int mask = 0; mask < MASKS; mask++) {
                keep = Math.max(keep, best[mask]);
            }

            out.append(n - keep).append('\n');
        }

        System.out.print(out);
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

            int c;

            do {
                c = read();
            } while (c <= ' ');

            int res = 0;

            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return res;
        }
    }
}
