
import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 10000000L;

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());

        while (t-- > 0) {

            int n = Integer.parseInt(br.readLine().trim());

            int[] a = new int[n];
            int sum = 0;

            StringTokenizer st = new StringTokenizer(br.readLine());

            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(st.nextToken());
                sum += a[i];
            }

            long[] dp = new long[sum + 1];
            dp[0] = 1;

            int curr = 0;

            for (int x : a) {
                for (int j = curr; j >= 0; j--) {
                    dp[j + x] = (dp[j + x] + dp[j]) % MOD;
                }
                curr += x;
            }

            long ans = 0;

            for (int x = 0; x <= sum; x++) {
                long contribution = Math.abs(2L * x - sum);
                ans = (ans + dp[x] * contribution) % MOD;
            }

            System.out.println(ans);
        }
    }
}

