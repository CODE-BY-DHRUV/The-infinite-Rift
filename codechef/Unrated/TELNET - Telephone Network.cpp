import java.io.*;
import java.util.*;

public class Main {

    static final long INF = Long.MAX_VALUE / 4;

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
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

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int N = fs.nextInt();
            int K = fs.nextInt();

            int[][] grid = new int[N][N];

            // positions[h] = all cells having height h
            ArrayList<int[]>[] positions = new ArrayList[K + 1];

            for (int h = 1; h <= K; h++) {
                positions[h] = new ArrayList<>();
            }

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    int h = fs.nextInt();
                    grid[i][j] = h;
                    positions[h].add(new int[]{i, j});
                }
            }

            /*
             * dp[i][j] is the minimum cost for reaching
             * cell (i,j) of the current height.
             */
            long[][] dp = new long[N][N];

            for (int i = 0; i < N; i++) {
                Arrays.fill(dp[i], INF);
            }

            // Every height-1 cell can be the starting point.
            for (int[] p : positions[1]) {
                dp[p[0]][p[1]] = 0;
            }

            for (int h = 1; h < K; h++) {

                /*
                 * We need:
                 *
                 * newDp[r][c] =
                 * min(dp[x][y] + |r-x| + |c-y|)
                 *
                 * for cells (r,c) having height h+1.
                 *
                 * First copy dp into dist.
                 */
                long[][] dist = new long[N][N];

                for (int i = 0; i < N; i++) {
                    System.arraycopy(dp[i], 0, dist[i], 0, N);
                }

                /*
                 * Four directional relaxations.
                 *
                 * These four passes compute the Manhattan
                 * distance transform.
                 */

                // Top-left direction
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {

                        if (i > 0 && dist[i - 1][j] != INF) {
                            dist[i][j] = Math.min(
                                    dist[i][j],
                                    dist[i - 1][j] + 1
                            );
                        }

                        if (j > 0 && dist[i][j - 1] != INF) {
                            dist[i][j] = Math.min(
                                    dist[i][j],
                                    dist[i][j - 1] + 1
                            );
                        }
                    }
                }

                // Bottom-right direction
                for (int i = N - 1; i >= 0; i--) {
                    for (int j = N - 1; j >= 0; j--) {

                        if (i + 1 < N && dist[i + 1][j] != INF) {
                            dist[i][j] = Math.min(
                                    dist[i][j],
                                    dist[i + 1][j] + 1
                            );
                        }

                        if (j + 1 < N && dist[i][j + 1] != INF) {
                            dist[i][j] = Math.min(
                                    dist[i][j],
                                    dist[i][j + 1] + 1
                            );
                        }
                    }
                }

                /*
                 * dist now contains:
                 *
                 * min over all previous-height cells p:
                 * dp[p] + ManhattanDistance(p, currentCell)
                 */

                long[][] newDp = new long[N][N];

                for (int i = 0; i < N; i++) {
                    Arrays.fill(newDp[i], INF);
                }

                for (int[] p : positions[h + 1]) {
                    int r = p[0];
                    int c = p[1];

                    newDp[r][c] = dist[r][c];
                }

                dp = newDp;
            }

            long answer = INF;

            for (int[] p : positions[K]) {
                answer = Math.min(answer, dp[p[0]][p[1]]);
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}