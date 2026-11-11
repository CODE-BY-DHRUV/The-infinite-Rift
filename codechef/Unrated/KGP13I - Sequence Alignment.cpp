
import java.util.*;

public class Main {

    static final int INF = 1000000000;

    static int solve(String A, String B, int x, int y) {

        int n = A.length();
        int m = B.length();

        int[][] dp = new int[n + 1][m + 1];

        for (int[] row : dp) {
            Arrays.fill(row, INF);
        }

        dp[0][0] = 0;

        for (int i = 0; i <= n; i++) {

            for (int j = 0; j <= m; j++) {

                if (dp[i][j] == INF) {
                    continue;
                }

                // 1. Match or replace
                if (i < n && j < m) {

                    int cost = (A.charAt(i) == B.charAt(j)) ? 0 : 1;

                    dp[i + 1][j + 1] = Math.min(
                        dp[i + 1][j + 1],
                        dp[i][j] + cost
                    );
                }

                // 2. Delete consecutive digits
                for (int len = 1; i + len <= n; len++) {

                    int cost = x + len;

                    dp[i + len][j] = Math.min(
                        dp[i + len][j],
                        dp[i][j] + cost
                    );
                }

                // 3. Insert consecutive digits
                for (int len = 1; j + len <= m; len++) {

                    int cost = Math.min(x + len, y);

                    dp[i][j + len] = Math.min(
                        dp[i][j + len],
                        dp[i][j] + cost
                    );
                }
            }
        }

        return dp[n][m];
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        for (int tc = 1; tc <= t; tc++) {

            int k = sc.nextInt();
            int l = sc.nextInt();

            String A = sc.next();
            String B = sc.next();

            int x = sc.nextInt();
            int y = sc.nextInt();

            int ans = solve(A, B, x, y);

            System.out.println("Case " + tc + ": " + ans);
        }

        sc.close();
    }
}
