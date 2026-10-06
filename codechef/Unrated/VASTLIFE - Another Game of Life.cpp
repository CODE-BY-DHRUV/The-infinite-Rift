
import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    static long[] transition(long[] dp, int[] b, int H) {

        int totalBits = H + 1;

        /*
         * cur state:
         *
         * Before processing any row:
         *   yMask = 0
         *   xSuffix = complete X column
         *
         * We store everything inside one array.
         */
        long[] cur = new long[1 << (H + 2)];

        for (int x = 0; x < (1 << totalBits); x++) {
            cur[x] = dp[x];
        }

        /*
         * Process every row of B.
         */
        for (int i = 0; i < H; i++) {

            int xBits = H + 1 - i;
            int nextXBits = xBits - 1;

            int newXMask = (1 << nextXBits) - 1;

            long[] next = new long[1 << (H + 2)];

            /*
             * IMPORTANT:
             *
             * After the previous iteration, we already know
             * y[0 ... i].
             *
             * Therefore there are i+1 known y bits.
             */
            int yCount = 1 << (i + 1);

            if (i == 0) {

                /*
                 * Initially no y bits exist.
                 *
                 * We choose y[0] and y[1].
                 */
                int oldXStates = 1 << xBits;

                for (int xSuffix = 0; xSuffix < oldXStates; xSuffix++) {

                    long ways = cur[xSuffix];

                    if (ways == 0) {
                        continue;
                    }

                    int xi = xSuffix & 1;
                    int xNext = (xSuffix >> 1) & 1;

                    int newXSuffix =
                            (xSuffix >> 1) & newXMask;

                    for (int y0 = 0; y0 <= 1; y0++) {

                        for (int y1 = 0; y1 <= 1; y1++) {

                            /*
                             * 2x2 block:
                             *
                             * xi      y0
                             * xNext   y1
                             *
                             * B = 1 iff exactly one diagonal
                             * is alive.
                             */
                            boolean alive =
                                    (xi == y1) &&
                                    (xNext == y0) &&
                                    (xi != xNext);

                            if ((alive ? 1 : 0) != b[i]) {
                                continue;
                            }

                            int yMask =
                                    y0 | (y1 << 1);

                            int key =
                                    yMask * (1 << nextXBits)
                                    + newXSuffix;

                            next[key] += ways;

                            if (next[key] >= MOD) {
                                next[key] -= MOD;
                            }
                        }
                    }
                }

            } else {

                int oldXStates = 1 << xBits;
                int newXSize = 1 << nextXBits;

                /*
                 * yMask has i+1 valid bits.
                 *
                 * THIS was the bug in the original code.
                 */
                for (int yMask = 0;
                     yMask < yCount;
                     yMask++) {

                    int base =
                            yMask * (1 << xBits);

                    /*
                     * y[i] is already known.
                     */
                    int yi =
                            (yMask >> i) & 1;

                    for (int xSuffix = 0;
                         xSuffix < oldXStates;
                         xSuffix++) {

                        long ways =
                                cur[base + xSuffix];

                        if (ways == 0) {
                            continue;
                        }

                        int xi =
                                xSuffix & 1;

                        int xNext =
                                (xSuffix >> 1) & 1;

                        int newXSuffix =
                                (xSuffix >> 1)
                                & newXMask;

                        /*
                         * Choose y[i+1].
                         */
                        for (int yNext = 0;
                             yNext <= 1;
                             yNext++) {

                            boolean alive =
                                    (xi == yNext) &&
                                    (xNext == yi) &&
                                    (xi != xNext);

                            if ((alive ? 1 : 0) != b[i]) {
                                continue;
                            }

                            int newYMask =
                                    yMask |
                                    (yNext << (i + 1));

                            int key =
                                    newYMask * newXSize
                                    + newXSuffix;

                            next[key] += ways;

                            if (next[key] >= MOD) {
                                next[key] -= MOD;
                            }
                        }
                    }
                }
            }

            cur = next;
        }

        /*
         * At this point:
         *
         *   y[0 ... H] is completely constructed.
         *   Only x[H] remains.
         *
         * Convert the state back into normal
         * column DP.
         */
        long[] result =
                new long[1 << (H + 1)];

        int finalXSize = 2;
        int ySize = 1 << (H + 1);

        for (int yMask = 0;
             yMask < ySize;
             yMask++) {

            int base =
                    yMask * finalXSize;

            long ways = 0;

            for (int xLast = 0;
                 xLast < 2;
                 xLast++) {

                ways += cur[base + xLast];

                if (ways >= MOD) {
                    ways -= MOD;
                }
            }

            result[yMask] = ways;
        }

        return result;
    }

    static long solve(int W, int H, int[][] B) {

        /*
         * A has:
         *
         *   H + 1 rows
         *   W + 1 columns
         *
         * Therefore every column has H+1 bits.
         */
        int states = 1 << (H + 1);

        /*
         * First column of A can be arbitrary.
         */
        long[] dp = new long[states];

        Arrays.fill(dp, 1);

        /*
         * Every column of B describes the relationship
         * between two consecutive columns of A.
         */
        for (int col = 0; col < W; col++) {

            int[] currentB = new int[H];

            for (int row = 0; row < H; row++) {
                currentB[row] = B[row][col];
            }

            dp = transition(dp, currentB, H);
        }

        /*
         * Sum over the final column of A.
         */
        long answer = 0;

        for (long ways : dp) {

            answer += ways;

            if (answer >= MOD) {
                answer -= MOD;
            }
        }

        return answer;
    }

    public static void main(String[] args)
            throws Exception {

        FastScanner fs =
                new FastScanner(System.in);

        StringBuilder out =
                new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int W = fs.nextInt();
            int H = fs.nextInt();

            int[][] B =
                    new int[H][W];

            for (int i = 0; i < H; i++) {

                for (int j = 0; j < W; j++) {

                    B[i][j] =
                            fs.nextInt();
                }
            }

            out.append(
                    solve(W, H, B)
            ).append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {

        private final InputStream in;

        private final byte[] buffer =
                new byte[1 << 16];

        private int ptr = 0;
        private int len = 0;

        FastScanner(InputStream in) {
            this.in = in;
        }

        private int read()
                throws IOException {

            if (ptr >= len) {

                len = in.read(buffer);
                ptr = 0;

                if (len <= 0) {
                    return -1;
                }
            }

            return buffer[ptr++];
        }

        int nextInt()
                throws IOException {

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

                result =
                        result * 10
                        + (c - '0');

                c = read();
            }

            return result * sign;
        }
    }
}
