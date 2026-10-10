
import java.io.*;
import java.math.BigInteger;

public class Main {

    static BigInteger gcd(BigInteger a, BigInteger b) {
        return a.gcd(b);
    }

    static void solve(FastScanner fs, StringBuilder out)
            throws IOException {

        long A = fs.nextLong();
        long B = fs.nextLong();
        long C = fs.nextLong();

        long D = fs.nextLong();
        long E = fs.nextLong();
        long F = fs.nextLong();

        long L = fs.nextLong();
        long R = fs.nextLong();

        // f(x) - g(x)
        long a = A - D;
        long b = B - E;
        long c = C - F;

        // Integral of ax^2 + bx + c from L to R:
        //
        // [a*x^3/3 + b*x^2/2 + c*x] from L to R
        //
        // Multiply by 6 to obtain an integer numerator.

        BigInteger l = BigInteger.valueOf(L);
        BigInteger r = BigInteger.valueOf(R);

        BigInteger numerator =
                BigInteger.valueOf(2 * a)
                        .multiply(r.pow(3).subtract(l.pow(3)))
                .add(BigInteger.valueOf(3 * b)
                        .multiply(r.pow(2).subtract(l.pow(2))))
                .add(BigInteger.valueOf(6 * c)
                        .multiply(r.subtract(l)));

        numerator = numerator.abs();

        BigInteger denominator = BigInteger.valueOf(6);
        BigInteger g = gcd(numerator, denominator);

        numerator = numerator.divide(g);
        denominator = denominator.divide(g);

        out.append(numerator)
           .append('/')
           .append(denominator)
           .append('\n');
    }

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int t = (int) fs.nextLong();

        while (t-- > 0) {
            solve(fs, out);
        }

        System.out.print(out);
    }

    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

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
            } while (c <= ' ' && c != -1);

            long num = 0;
            int sign = 1;

            if (c == '-') {
                sign = -1;
                c = read();
            }

            while (c > ' ') {
                num = num * 10 + c - '0';
                c = read();
            }

            return num * sign;
        }
    }
}
