
import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;
    static final long PHI = MOD - 1;

    static final int MAX = 100000;

    static long[] fact = new long[MAX + 1];
    static long[] invFact = new long[MAX + 1];

    static int[] primes;
    static boolean[] composite;

    static long modPow(long a, long b, long mod) {
        long res = 1;

        a %= mod;

        while (b > 0) {
            if ((b & 1) != 0) {
                res = res * a % mod;
            }

            a = a * a % mod;
            b >>= 1;
        }

        return res;
    }

    static void precompute() {

        // Factorials modulo MOD
        fact[0] = 1;

        for (int i = 1; i <= MAX; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        invFact[MAX] = modPow(fact[MAX], MOD - 2, MOD);

        for (int i = MAX; i >= 1; i--) {
            invFact[i - 1] = invFact[i] * i % MOD;
        }

        // Sieve of Eratosthenes
        composite = new boolean[MAX + 1];

        ArrayList<Integer> list = new ArrayList<>();

        for (int i = 2; i <= MAX; i++) {

            if (!composite[i]) {

                list.add(i);

                if ((long) i * i <= MAX) {
                    for (int j = i * i; j <= MAX; j += i) {
                        composite[j] = true;
                    }
                }
            }
        }

        primes = new int[list.size()];

        for (int i = 0; i < list.size(); i++) {
            primes[i] = list.get(i);
        }
    }

    // Binomial coefficient modulo MOD
    static long nCr(int n, int r) {

        if (r < 0 || r > n) {
            return 0;
        }

        return fact[n] * invFact[r] % MOD
                * invFact[n - r] % MOD;
    }

    // Legendre's formula:
    // Exponent of prime p in n!
    static long factorialPower(int n, int p) {

        long result = 0;

        while (n > 0) {
            n /= p;
            result += n;
        }

        return result;
    }

    // Calculate C(n,r) modulo PHI.
    // PHI is composite, so we use prime factorization.
    static long nCrPhi(int n, int r) {

        if (r < 0 || r > n) {
            return 0;
        }

        r = Math.min(r, n - r);

        long result = 1;

        for (int p : primes) {

            if (p > n) break;

            long exponent =
                    factorialPower(n, p)
                    - factorialPower(r, p)
                    - factorialPower(n - r, p);

            if (exponent > 0) {
                result = result * modPow(p, exponent, PHI) % PHI;
            }
        }

        return result;
    }

    // Calculate P ^ C(n,r) modulo MOD
    static long powerOfCombination(long P, int n, int r) {

        if (r < 0 || r > n) {
            return 1;
        }

        // The binomial coefficient is positive.
        // Handle P = 0 separately.
        if (P == 0) {
            return 0;
        }

        long exponent = nCrPhi(n, r);

        return modPow(P, exponent, MOD);
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner(System.in);

        precompute();

        int t = fs.nextInt();

        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {

            int m = fs.nextInt();

            long P = 1;

            for (int i = 0; i < m; i++) {

                long base = fs.nextLong();
                long power = fs.nextLong();

                P = P * (power % MOD) % MOD;
            }

            // Maximum antichain size
            int k = m / 2;

            long maxSize = nCr(m, k);

            long ways;

            if (m % 2 == 0) {

                // One middle rank
                ways = powerOfCombination(
                        P,
                        m - 1,
                        k - 1
                );

            } else {

                // Two middle ranks
                long first = powerOfCombination(
                        P,
                        m - 1,
                        k - 1
                );

                long second = powerOfCombination(
                        P,
                        m - 1,
                        m - k - 1
                );

                ways = (first + second) % MOD;
            }

            sb.append(maxSize)
              .append(' ')
              .append(ways)
              .append('\n');
        }

        System.out.print(sb);
    }

    static class FastScanner {

        private final InputStream in;

        private final byte[] buffer = new byte[1 << 16];

        private int ptr = 0;
        private int len = 0;

        FastScanner(InputStream in) {
            this.in = in;
        }

        private int read() throws IOException {

            if (ptr >= len) {

                len = in.read(buffer);
                ptr = 0;

                if (len <= 0) return -1;
            }

            return buffer[ptr++];
        }

        long nextLong() throws IOException {

            int c;

            do {
                c = read();
            } while (c <= 32 && c != -1);

            long num = 0;

            while (c > 32) {
                num = num * 10 + c - '0';
                c = read();
            }

            return num;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}
