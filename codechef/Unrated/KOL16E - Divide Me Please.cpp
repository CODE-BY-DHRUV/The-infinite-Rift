import java.io.*;
import java.util.*;

public class Main {

    static long modPow(long a, long e, long mod) {
        long result = 1;
        while (e > 0) {
            if ((e & 1) != 0) {
                result = result * a % mod;
            }
            a = a * a % mod;
            e >>= 1;
        }
        return result;
    }

    static long smallestN(long p) {
        long m = p - 1;
        long x = m;

        List<Long> factors = new ArrayList<>();

        for (long d = 2; d * d <= x; d++) {
            if (x % d == 0) {
                factors.add(d);
                while (x % d == 0) {
                    x /= d;
                }
            }
        }

        if (x > 1) factors.add(x);

        for (long f : factors) {
            while (m % f == 0 && modPow(10, m / f, p) == 1) {
                m /= f;
            }
        }

        // m is the multiplicative order of 10 modulo p.
        // If m is even, 10^(m/2) is -1 modulo p.
        if (m % 2 == 0) {
            return m / 2;
        }

        return m;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        for (int tc = 1; tc <= T; tc++) {
            long p = Long.parseLong(br.readLine().trim());
            long order = smallestN(p);

            long value = modPow(10, order, p);
            String method = (value == 1) ? "sum" : "altersum";

            out.append("Case ").append(tc).append(": ")
               .append(order).append("-").append(method).append('\n');
        }

        System.out.print(out);
    }
}
