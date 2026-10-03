import java.io.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

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
            } while (c <= ' ');

            long res = 0;

            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return res;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }

    // Returns k such that S = base * 2^k.
    // Returns -1 if S cannot be formed from base tiles.
    static int getExponent(long S, long base) {
        if (S % base != 0) {
            return -1;
        }

        long value = S / base;
        int k = 0;

        while (value % 2 == 0) {
            value /= 2;
            k++;
        }

        return value == 1 ? k : -1;
    }

    static long modPow(long a, long e) {
        long result = 1;

        while (e > 0) {
            if ((e & 1) != 0) {
                result = result * a % MOD;
            }

            a = a * a % MOD;
            e >>= 1;
        }

        return result;
    }

    static long modInverse(long x) {
        return modPow(x, MOD - 2);
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            long X = fs.nextLong();
            long Y = fs.nextLong();
            long S = fs.nextLong();

            long u = fs.nextLong();
            long v = fs.nextLong();

            int kX = getExponent(S, X);

            long answer;

            if (kX != -1) {
                // S = X * 2^kX
                // Need 2^kX type-1 tiles.
                long needed = modPow(2, kX);

                // Expected = needed / (u/v)
                //         = needed * v / u
                answer = needed;
                answer = answer * (v % MOD) % MOD;
                answer = answer * modInverse(u % MOD) % MOD;

            } else {
                int kY = getExponent(S, Y);

                // Guaranteed that S can be formed.
                // S = Y * 2^kY
                // Need 2^kY type-2 tiles.

                long needed = modPow(2, kY);

                // Probability of type 2 = (v-u)/v
                // Expected = needed * v / (v-u)
                answer = needed;
                answer = answer * (v % MOD) % MOD;
                answer = answer * modInverse((v - u) % MOD) % MOD;
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}
