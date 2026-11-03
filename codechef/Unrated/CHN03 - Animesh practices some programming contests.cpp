import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );
        StringTokenizer st;

        int nextInt() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return Integer.parseInt(st.nextToken());
        }
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner();
        StringBuilder sb = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();
            int k = fs.nextInt();
            int maxTime = fs.nextInt();

            int[][] time = new int[n][3];
            int[][] pleasure = new int[n][3];

            // Read time values
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 3; j++) {
                    time[i][j] = fs.nextInt();
                }
            }

            // Read pleasure values
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 3; j++) {
                    pleasure[i][j] = fs.nextInt();
                }
            }

            // At most n-1 swaps are ever necessary
            int maxK = Math.min(k, n - 1);

            // dp[count][swaps][time]
            long[][][] dp = new long[n + 1][maxK + 1][maxTime + 1];

            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= maxK; j++) {
                    Arrays.fill(dp[i][j], -1);
                }
            }

            dp[0][0][0] = 0;

            // Process each contest
            for (int i = 0; i < n; i++) {

                // Precompute all 8 subsets
                int[] subCount = new int[8];
                int[] subTime = new int[8];
                int[] subSwap = new int[8];
                long[] subPleasure = new long[8];

                for (int mask = 0; mask < 8; mask++) {

                    for (int j = 0; j < 3; j++) {

                        if ((mask & (1 << j)) != 0) {

                            subCount[mask]++;
                            subTime[mask] += time[i][j];
                            subPleasure[mask] += pleasure[i][j];
                        }
                    }

                    if (subCount[mask] > 0) {
                        subSwap[mask] = subCount[mask] - 1;
                    }
                }

                long[][][] ndp =
                    new long[n + 1][maxK + 1][maxTime + 1];

                for (int c = 0; c <= n; c++) {
                    for (int s = 0; s <= maxK; s++) {
                        for (int t = 0; t <= maxTime; t++) {

                            if (dp[c][s][t] == -1) {
                                continue;
                            }

                            long current = dp[c][s][t];

                            // Try all subsets of current contest
                            for (int mask = 0; mask < 8; mask++) {

                                int nc = c + subCount[mask];
                                int ns = s + subSwap[mask];
                                int nt = t + subTime[mask];

                                if (nc > n || ns > maxK || nt > maxTime) {
                                    continue;
                                }

                                long np = current + subPleasure[mask];

                                ndp[nc][ns][nt] =
                                    Math.max(ndp[nc][ns][nt], np);
                            }
                        }
                    }
                }

                dp = ndp;
            }

            // Find maximum pleasure
            long ans = 0;

            for (int c = 0; c <= n; c++) {
                for (int s = 0; s <= maxK; s++) {
                    for (int t = 0; t <= maxTime; t++) {

                        ans = Math.max(ans, dp[c][s][t]);
                    }
                }
            }

            sb.append(ans).append('\n');
        }

        System.out.print(sb);
    }
}