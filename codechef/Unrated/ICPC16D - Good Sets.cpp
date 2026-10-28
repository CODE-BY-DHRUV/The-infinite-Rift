
import java.io.*;
import java.util.*;

public class Main {
    static final int MOD = 1_000_000_007;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder output = new StringBuilder();

        while (T-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());

            int[] a = new int[n];
            StringTokenizer st = new StringTokenizer("");

            while (st.countTokens() < n) {
                st = new StringTokenizer(
                    br.readLine()
                );
                if (st.countTokens() == 0) {
                    continue;
                }
                break;
            }

            int max = 0;
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(st.nextToken());
                max = Math.max(max, a[i]);
            }

            boolean[] present = new boolean[max + 1];
            long[] dp = new long[max + 1];

            for (int x : a) {
                present[x] = true;
                dp[x] = 1;
            }

            long answer = 0;

            for (int x = 1; x <= max; x++) {
                if (!present[x]) {
                    continue;
                }

                answer = (answer + dp[x]) % MOD;

                for (int multiple = x * 2;
                     multiple <= max;
                     multiple += x) {

                    if (present[multiple]) {
                        dp[multiple] =
                            (dp[multiple] + dp[x]) % MOD;
                    }
                }
            }

            output.append(answer).append('\n');
        }

        System.out.print(output);
    }
}
