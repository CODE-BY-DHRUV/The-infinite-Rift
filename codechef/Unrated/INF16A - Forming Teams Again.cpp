
import java.io.*;
import java.util.*;

public class Main {

    static long mod;

    // Modular exponentiation
    static long pow(long a, long b) {
        long res = 1;
        a %= mod;

        while (b > 0) {
            if ((b & 1) == 1) {
                res = (res * a) % mod;
            }

            a = (a * a) % mod;
            b >>= 1;
        }

        return res;
    }

    // Calculate exponent of mod in n!
    static long factorialPower(long n) {
        long ans = 0;

        while (n > 0) {
            n /= mod;
            ans += n;
        }

        return ans;
    }

    // Calculate n! after removing all factors of mod
    static long unitFactorial(long n) {

        long res = 1;

        while (n > 0) {

            long blocks = n / mod;
            int rem = (int)(n % mod);

            // (mod - 1)! = -1 (mod mod)
            if ((blocks & 1) == 1) {
                res = (mod - res) % mod;
            }

            // Multiply by rem!
            for (int i = 1; i <= rem; i++) {
                res = (res * i) % mod;
            }

            n = blocks;
        }

        return res;
    }

    // Number of partitions for a fixed team size
    static long calculate(long n, long k) {

        long m = n / k;

        long power = factorialPower(n)
                   - m * factorialPower(k)
                   - factorialPower(m);

        // Divisible by mod
        if (power > 0) {
            return 0;
        }

        long a = unitFactorial(n);
        long b = unitFactorial(k);
        long c = unitFactorial(m);

        long denominator = (pow(b, m) * c) % mod;

        // Modular inverse using Fermat's theorem
        long inverse = pow(denominator, mod - 2);

        return (a * inverse) % mod;
    }

    // Find the prime factors of N
    static long[] factorize(long n) {

        for (long i = 2; i * i <= n; i++) {

            if (n % i == 0) {
                return new long[]{i, n / i};
            }
        }

        return new long[]{n, 1};
    }

    static long solve(long n) {

        long[] factors = factorize(n);

        long p1 = factors[0];
        long p2 = factors[1];

        long ans = 0;

        // Team size 1
        ans = (ans + calculate(n, 1)) % mod;

        // Team size p1
        ans = (ans + calculate(n, p1)) % mod;

        // Team size p2 (avoid duplicate when p1 == p2)
        if (p1 != p2) {
            ans = (ans + calculate(n, p2)) % mod;
        }

        // Team size N
        ans = (ans + calculate(n, n)) % mod;

        return ans;
    }

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());

        StringBuilder sb = new StringBuilder();

        for (int tc = 1; tc <= t; tc++) {

            StringTokenizer st = new StringTokenizer(br.readLine());

            int L = Integer.parseInt(st.nextToken());
            mod = Long.parseLong(st.nextToken());

            sb.append("Case ").append(tc).append(":\n");

            for (int i = 0; i < L; i++) {

                long n = Long.parseLong(br.readLine().trim());

                sb.append(solve(n)).append('\n');
            }
        }

        System.out.print(sb);
    }
}

