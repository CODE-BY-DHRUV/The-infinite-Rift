
import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;
    static final int MAX = 5000;

    static long[] fact = new long[MAX + 1];
    static long[] invFact = new long[MAX + 1];

    static long power(long a, long b) {

        long result = 1;

        while (b > 0) {

            if ((b & 1) == 1) {
                result = result * a % MOD;
            }

            a = a * a % MOD;
            b >>= 1;
        }

        return result;
    }

    static void precompute() {

        fact[0] = 1;

        for (int i = 1; i <= MAX; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        invFact[MAX] = power(fact[MAX], MOD - 2);

        for (int i = MAX - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }
    }

    static long nCr(int n, int r) {

        if (r < 0 || r > n) {
            return 0;
        }

        return fact[n] * invFact[r] % MOD
                * invFact[n - r] % MOD;
    }

    static long solve(int n) {

        long ans = 0;
        long power25 = 1;

        for (int k = 1; k <= n; k++) {

            long combinations = nCr(n, k);

            long ways = combinations * combinations % MOD;

            long contribution = 26 * power25 % MOD;

            contribution = contribution * ways % MOD;

            ans = (ans + contribution) % MOD;

            power25 = power25 * 25 % MOD;
        }

        return ans;
    }

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());

        precompute();

        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {

            int n = Integer.parseInt(br.readLine().trim());

            sb.append(solve(n)).append('\n');
        }

        System.out.print(sb);
    }
}
