import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        for (int tc = 1; tc <= T; tc++) {
            int N = sc.nextInt();

            int[] P = new int[N];
            int[] F = new int[N];

            for (int i = 0; i < N; i++) {
                P[i] = (int) Math.round(sc.nextDouble() * 100);
            }

            for (int i = 0; i < N; i++) {
                F[i] = sc.nextInt();
            }

            int S = (int) Math.round(sc.nextDouble() * 100);

            int[] dp = new int[N + 1];
            Arrays.fill(dp, -1);
            dp[0] = 0;

            int sumP = 0;

            for (int i = 0; i < N; i++) {
                sumP += P[i];

                int battlesPlayed = i + 1;

                // Find the maximum valid number of wins.
                int maxWins = 0;
                while (100 * (maxWins + 1)
                        < sumP + battlesPlayed * S) {
                    maxWins++;
                }

                // 0/1 Knapsack: update in descending order.
                for (int wins = i + 1; wins >= 1; wins--) {
                    if (wins <= maxWins && dp[wins - 1] != -1) {
                        dp[wins] = Math.max(
                            dp[wins],
                            dp[wins - 1] + F[i]
                        );
                    }
                }

                // Remove states that violate the PEB constraint.
                for (int wins = maxWins + 1; wins <= i + 1; wins++) {
                    dp[wins] = -1;
                }
            }

            int answer = 0;
            for (int value : dp) {
                answer = Math.max(answer, value);
            }

            System.out.println("Case " + tc + ": " + answer);
        }

        sc.close();
    }
}