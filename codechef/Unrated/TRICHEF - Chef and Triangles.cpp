import java.io.*;
import java.util.*;

public class Main {

    static final int MAX_SUM = 2_000_000;

    // Sum of |a[i] - a[j]| for all i < j
    static long pairwiseDifference(long[] a, int n) {
        long ans = 0;
        long prefix = 0;

        for (int i = 0; i < n; i++) {
            ans += a[i] * i - prefix;
            prefix += a[i];
        }

        return ans;
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int N = fs.nextInt();

            long[][] groups = new long[3][N];
            int[] size = new int[3];

            // Store y-coordinates according to x = 1, 2, 3
            for (int i = 0; i < N; i++) {
                int x = fs.nextInt();
                long y = fs.nextLong();

                groups[x - 1][size[x - 1]++] = y;
            }

            // Sort each group
            for (int i = 0; i < 3; i++) {
                Arrays.sort(groups[i], 0, size[i]);
            }

            long doubledAnswer = 0;

            /*
             * Case 1:
             * Two points have the same x-coordinate.
             *
             * If their y-values are u and v and the third point
             * is at x = q, then:
             *
             * 2 * Area = |p - q| * |u - v|
             */

            // x = 1
            long d1 = pairwiseDifference(groups[0], size[0]);
            doubledAnswer += d1 * size[1];       // x = 2
            doubledAnswer += d1 * 2L * size[2];  // x = 3

            // x = 2
            long d2 = pairwiseDifference(groups[1], size[1]);
            doubledAnswer += d2 * size[0];       // x = 1
            doubledAnswer += d2 * size[2];       // x = 3

            // x = 3
            long d3 = pairwiseDifference(groups[2], size[2]);
            doubledAnswer += d3 * 2L * size[0];  // x = 1
            doubledAnswer += d3 * size[1];       // x = 2


            /*
             * Case 2:
             * One point from each x = 1, 2, 3.
             *
             * 2 * Area = |y1 - 2*y2 + y3|
             *
             * Let:
             *     s = y1 + y3
             *
             * Then:
             *     2 * Area = |s - 2*y2|
             *
             * Count all possible s using frequency array.
             */

            if (size[0] > 0 && size[1] > 0 && size[2] > 0) {

                int[] freq = new int[MAX_SUM + 1];

                // Build frequency of y1 + y3
                for (int i = 0; i < size[0]; i++) {
                    for (int j = 0; j < size[2]; j++) {

                        int sum = (int) (groups[0][i] + groups[2][j]);
                        freq[sum]++;
                    }
                }

                long[] prefixCount = new long[MAX_SUM + 1];
                long[] prefixSum = new long[MAX_SUM + 1];

                long count = 0;
                long sum = 0;

                for (int s = 0; s <= MAX_SUM; s++) {

                    count += freq[s];
                    sum += (long) freq[s] * s;

                    prefixCount[s] = count;
                    prefixSum[s] = sum;
                }

                long totalCount = count;
                long totalSum = sum;

                // Process every y2
                for (int i = 0; i < size[1]; i++) {

                    long target = 2L * groups[1][i];
                    int t = (int) target;

                    // s <= target
                    long leftCount = prefixCount[t];
                    long leftSum = prefixSum[t];

                    long leftContribution =
                            target * leftCount - leftSum;

                    // s > target
                    long rightCount = totalCount - leftCount;
                    long rightSum = totalSum - leftSum;

                    long rightContribution =
                            rightSum - target * rightCount;

                    doubledAnswer +=
                            leftContribution + rightContribution;
                }
            }

            // Actual area = doubledArea / 2
            if ((doubledAnswer & 1L) == 0) {
                out.append(doubledAnswer / 2).append(".0\n");
            } else {
                out.append(doubledAnswer / 2).append(".5\n");
            }
        }

        System.out.print(out);
    }


    // Fast input
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

            boolean negative = false;

            if (c == '-') {
                negative = true;
                c = read();
            }

            long result = 0;

            while (c > ' ') {
                result = result * 10 + (c - '0');
                c = read();
            }

            return negative ? -result : result;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}