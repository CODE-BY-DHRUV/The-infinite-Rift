import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Main {
    static final long INF = 1L << 60;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        String line = br.readLine();
        if (line == null || line.trim().isEmpty()) return;
        st = new StringTokenizer(line);
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        int[] S = new int[M];
        int idx = 0;
        while (idx < M) {
            while (st == null || !st.hasMoreTokens()) {
                line = br.readLine();
                if (line == null) break;
                st = new StringTokenizer(line);
            }
            if (line == null) break;
            S[idx++] = Integer.parseInt(st.nextToken());
        }

        // 1. Calculate f(u) = weight of node u
        // Depth(s1) appears once at start.
        // Each transition s_i -> s_{i+1} adds Depth(s_i) + Depth(s_{i+1}) - 2*Depth(LCA).
        long[] f = new long[N + 1];
        f[S[0]] += 1;
        for (int i = 0; i < M - 1; ++i) {
            f[S[i]] += 1;
            f[S[i + 1]] += 1;
        }

        // Prefix sum of f
        long[] pref_f = new long[N + 1];
        for (int i = 1; i <= N; ++i) {
            pref_f[i] = pref_f[i - 1] + f[i];
        }

        // 2. Count transitions where both endpoints u, v are present
        long[][] pair_cnt = new long[N + 1][N + 1];
        for (int i = 0; i < M - 1; ++i) {
            int u = S[i];
            int v = S[i + 1];
            pair_cnt[u][v]++;
        }

        // 2D Prefix Sums to quickly query internal pair count in range [L, R]
        long[][] pref_pair = new long[N + 1][N + 1];
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                pref_pair[i][j] = pair_cnt[i][j] 
                                + pref_pair[i - 1][j] 
                                + pref_pair[i][j - 1] 
                                - pref_pair[i - 1][j - 1];
            }
        }

        // Helper lambda/function for CostIncrease(L, R)
        // CostIncrease(L, R) = sum_{u=L..R} f(u) - 2 * (number of transitions with both endpoints in [L, R])
        // If L > R, cost increase is 0.

        long[][] dp = new long[N + 2][N + 2];

        for (int len = 2; len <= N; ++len) {
            for (int i = 1; i <= N - len + 1; ++i) {
                int j = i + len - 1;
                long minCost = INF;

                for (int k = i; k <= j; ++k) {
                    long leftDP = dp[i][k - 1];
                    long rightDP = dp[k + 1][j];

                    long leftInc = 0;
                    if (i <= k - 1) {
                        long nodeW = pref_f[k - 1] - pref_f[i - 1];
                        long internalPairs = pref_pair[k - 1][k - 1] 
                                           - pref_pair[i - 1][k - 1] 
                                           - pref_pair[k - 1][i - 1] 
                                           + pref_pair[i - 1][i - 1];
                        leftInc = nodeW - 2 * internalPairs;
                    }

                    long rightInc = 0;
                    if (k + 1 <= j) {
                        long nodeW = pref_f[j] - pref_f[k];
                        long internalPairs = pref_pair[j][j] 
                                           - pref_pair[k][j] 
                                           - pref_pair[j][k] 
                                           + pref_pair[k][k];
                        rightInc = nodeW - 2 * internalPairs;
                    }

                    long cost = leftDP + rightDP + leftInc + rightInc;
                    if (cost < minCost) {
                        minCost = cost;
                    }
                }
                dp[i][j] = minCost;
            }
        }

        System.out.println(dp[1][N]);
    }
}