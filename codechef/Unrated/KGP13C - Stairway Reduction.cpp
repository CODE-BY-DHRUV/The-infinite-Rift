
import java.util.*;

public class Main {

    static final long INF = Long.MAX_VALUE / 4;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        for (int tc = 1; tc <= T; tc++) {

            int K = sc.nextInt();
            int M = sc.nextInt();
            long w = sc.nextLong();

            long[] l = new long[K];
            long[] h = new long[K];

            for (int i = 0; i < K; i++) {
                l[i] = sc.nextLong();
                h[i] = sc.nextLong();
            }

            // Precompute the cost of merging
            // every contiguous segment [i, j).

            long[][] cost = new long[K][K + 1];

            for (int i = 0; i < K; i++) {

                long sumLength = 0;

                for (int j = i + 1; j <= K; j++) {

                    cost[i][j] = cost[i][j - 1]
                               + sumLength * h[j - 1] * w;

                    sumLength += l[j - 1];
                }
            }

            // DP: dp[m][j] = minimum cost of
            // converting first j steps into m steps.

            long[][] dp = new long[M + 1][K + 1];

            for (int i = 0; i <= M; i++) {
                Arrays.fill(dp[i], INF);
            }

            dp[0][0] = 0;

            for (int m = 1; m <= M; m++) {

                for (int j = m; j <= K; j++) {

                    for (int i = m - 1; i < j; i++) {

                        if (dp[m - 1][i] == INF) {
                            continue;
                        }

                        long current = dp[m - 1][i]
                                     + cost[i][j];

                        dp[m][j] = Math.min(dp[m][j], current);
                    }
                }
            }

            System.out.println("Case " + tc + ": " + dp[M][K]);
        }

        sc.close();
    }
}
