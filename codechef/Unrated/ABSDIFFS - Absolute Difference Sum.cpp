import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    /*
     * Returns:
     * sum of scores of all integers from 0 to n.
     */
    static long solve(long n) {
        if (n <= 0) return 0;

        String s = Long.toString(n);
        int len = s.length();

        /*
         * dp[tight][started]
         *
         * cnt  = number of prefixes
         * sum[d] = total occurrences of digit d
         * pair   = total score of all prefixes
         *
         * We keep the 10 digit occurrence sums.
         */
        long[][] cnt = new long[2][2];
        long[][][] sum = new long[2][2][10];
        long[][] pair = new long[2][2];

        cnt[1][0] = 1;

        for (int pos = 0; pos < len; pos++) {

            long[][] nextCnt = new long[2][2];
            long[][][] nextSum = new long[2][2][10];
            long[][] nextPair = new long[2][2];

            int limitDigit = s.charAt(pos) - '0';

            for (int tight = 0; tight <= 1; tight++) {
                for (int started = 0; started <= 1; started++) {

                    long ways = cnt[tight][started];

                    if (ways == 0) continue;

                    int limit = tight == 1 ? limitDigit : 9;

                    for (int d = 0; d <= limit; d++) {

                        int ntight =
                                (tight == 1 && d == limitDigit) ? 1 : 0;

                        int nstarted =
                                (started == 1 || d != 0) ? 1 : 0;

                        long w = ways;

                        nextCnt[ntight][nstarted] =
                                (nextCnt[ntight][nstarted] + w) % MOD;

                        /*
                         * Copy previous digit occurrence sums.
                         */
                        for (int x = 0; x <= 9; x++) {
                            nextSum[ntight][nstarted][x] =
                                    (nextSum[ntight][nstarted][x]
                                            + sum[tight][started][x]) % MOD;
                        }

                        /*
                         * Leading zeroes are not digits of the number.
                         */
                        if (nstarted == 1) {

                            /*
                             * Add the new digit d.
                             */
                            nextSum[ntight][nstarted][d] =
                                    (nextSum[ntight][nstarted][d] + w)
                                            % MOD;

                            /*
                             * Every previous digit x contributes
                             * |x-d| with the new digit.
                             */
                            long contribution = 0;

                            for (int x = 0; x <= 9; x++) {
                                long occurrences =
                                        sum[tight][started][x];

                                contribution =
                                        (contribution
                                                + occurrences
                                                * Math.abs(x - d))
                                                % MOD;
                            }

                            /*
                             * Existing pair contributions remain.
                             */
                            nextPair[ntight][nstarted] =
                                    (nextPair[ntight][nstarted]
                                            + pair[tight][started]
                                            + contribution)
                                            % MOD;

                        } else {

                            /*
                             * Still leading zero.
                             * No actual digit has been added.
                             */
                            nextPair[ntight][nstarted] =
                                    (nextPair[ntight][nstarted]
                                            + pair[tight][started])
                                            % MOD;
                        }
                    }
                }
            }

            cnt = nextCnt;
            sum = nextSum;
            pair = nextPair;
        }

        long ans = 0;

        for (int tight = 0; tight <= 1; tight++) {
            ans = (ans + pair[tight][1]) % MOD;
        }

        return ans;
    }

    static long range(long L, long R) {
        long right = solve(R);
        long left = solve(L - 1);

        return (right - left + MOD) % MOD;
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();

        int T = fs.nextInt();

        StringBuilder out = new StringBuilder();

        while (T-- > 0) {

            long L = fs.nextLong();
            long R = fs.nextLong();

            out.append(range(L, R)).append('\n');
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

                if (len <= 0)
                    return -1;
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