
import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr, len;

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

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }

    static void update(int[][] bit, int s, int idx,
                       int value, int size) {
        for (int p = idx; p <= size; p += p & -p) {
            bit[s][p] = Math.max(bit[s][p], value);
        }
    }

    static int query(int[][] bit, int s, int idx) {
        int result = 0;
        for (int p = idx; p > 0; p -= p & -p) {
            result = Math.max(result, bit[s][p]);
        }
        return result;
    }

    static int solve(int n, long L, long R, long[] input) {
        long[] validTemp = new long[n];
        int count = 0;

        for (long x : input) {
            if (x >= 0 && x + R <= L) {
                validTemp[count++] = x;
            }
        }

        if (count == 0) {
            return n;
        }

        long[] x = Arrays.copyOf(validTemp, count);
        Arrays.sort(x);

        long slack = L / R - n;
        int maxDrops = (int) Math.min((long) n, slack);

        long[] residues = new long[count];
        for (int i = 0; i < count; i++) {
            residues[i] = x[i] % R;
        }

        long[] sortedResidues = residues.clone();
        Arrays.sort(sortedResidues);

        int size = 0;
        for (long v : sortedResidues) {
            if (size == 0 || sortedResidues[size - 1] != v) {
                sortedResidues[size++] = v;
            }
        }
        sortedResidues = Arrays.copyOf(sortedResidues, size);

        int[] rank = new int[count];
        for (int i = 0; i < count; i++) {
            rank[i] = Arrays.binarySearch(sortedResidues, residues[i]) + 1;
        }

        // dp[i][s] = maximum untouched segments ending at i
        // with exactly s decreases in consecutive remainders.
        int[][] dp = new int[count][maxDrops + 1];

        int[][] low = new int[maxDrops + 1][size + 1];
        int[][] high = new int[maxDrops + 1][size + 1];

        int add = 0;

        for (int i = 0; i < count; i++) {

            // Add all previous segments that do not overlap with i.
            while (add < i && x[add] + R <= x[i]) {
                int q = rank[add];

                for (int s = 0; s <= maxDrops; s++) {
                    if (dp[add][s] == 0) continue;

                    update(low, s, q, dp[add][s], size);
                    update(high, s, size - q + 1,
                           dp[add][s], size);
                }
                add++;
            }

            // Keep this segment as the first untouched segment.
            dp[i][0] = 1;

            int q = rank[i];

            for (int s = 0; s <= maxDrops; s++) {
                // Previous remainder <= current remainder:
                // no additional decrease.
                int best = query(low, s, q);
                if (best > 0) {
                    dp[i][s] = Math.max(dp[i][s], best + 1);
                }

                // Previous remainder > current remainder:
                // one additional decrease.
                if (s > 0) {
                    int bestDrop = query(high, s - 1, size - q);
                    if (bestDrop > 0) {
                        dp[i][s] = Math.max(
                            dp[i][s], bestDrop + 1
                        );
                    }
                }
            }
        }

        int maxKept = 0;
        long endRemainder = L % R;

        for (int i = 0; i < count; i++) {
            int endCost = residues[i] > endRemainder ? 1 : 0;

            for (int s = 0; s <= maxDrops; s++) {
                if ((long) s + endCost <= slack) {
                    maxKept = Math.max(maxKept, dp[i][s]);
                }
            }
        }

        return n - maxKept;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {
            int n = fs.nextInt();
            long L = fs.nextLong();
            long R = fs.nextLong();

            long[] x = new long[n];
            for (int i = 0; i < n; i++) {
                x[i] = fs.nextLong();
            }

            out.append(solve(n, L, R, x)).append('\n');
        }

        System.out.print(out);
    }
}

