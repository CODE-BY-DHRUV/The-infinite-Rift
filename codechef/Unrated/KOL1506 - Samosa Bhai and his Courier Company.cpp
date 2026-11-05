
import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    static long modPow(long a, int b) {
        long res = 1;
        while (b > 0) {
            if ((b & 1) == 1) {
                res = res * a % MOD;
            }
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    static long solve(int n, int k, long[] a) {

        Arrays.sort(a);

        // Precompute binomial coefficients
        long[][] C = new long[k + 1][k + 1];

        C[0][0] = 1;

        for (int i = 1; i <= k; i++) {
            C[i][0] = 1;
            C[i][i] = 1;

            for (int j = 1; j < i; j++) {
                C[i][j] = (C[i - 1][j - 1]
                         + C[i - 1][j]) % MOD;
            }
        }

        // prefix[p] = sum of previous A[i]^p
        long[] prefix = new long[k + 1];

        long ans = 0;

        for (int i = 0; i < n; i++) {

            long[] power = new long[k + 1];

            power[0] = 1;

            for (int p = 1; p <= k; p++) {
                power[p] = power[p - 1] * a[i] % MOD;
            }

            // Calculate contribution with all previous houses
            for (int p = 0; p <= k; p++) {

                int q = k - p;

                long term = C[k][p] * power[p] % MOD;
                term = term * prefix[q] % MOD;

                if ((q & 1) == 1) {
                    ans = (ans - term + MOD) % MOD;
                } else {
                    ans = (ans + term) % MOD;
                }
            }

            // Add current house powers to prefix sums
            for (int p = 0; p <= k; p++) {
                prefix[p] = (prefix[p] + power[p]) % MOD;
            }
        }

        // Each pair sends gifts in both directions
        return (2 * ans) % MOD;
    }

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in));

        int t = Integer.parseInt(br.readLine().trim());

        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {

            StringTokenizer st =
                new StringTokenizer(br.readLine());

            int n = Integer.parseInt(st.nextToken());
            int k = Integer.parseInt(st.nextToken());

            long[] a = new long[n];

            st = new StringTokenizer(br.readLine());

            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
            }

            sb.append(solve(n, k, a)).append('\n');
        }

        System.out.print(sb);
    }
}
