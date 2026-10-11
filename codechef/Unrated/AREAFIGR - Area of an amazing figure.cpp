
import java.io.*;
import java.util.*;

public class Main {
    static final double SQRT3 = Math.sqrt(3.0);
    static final int STEPS = 20000; // Must be even

    static double height(double x, double a,
                         double r1, double r2, double r3) {
        double low = 0.0;
        double high = SQRT3 * (a - Math.abs(x));

        // Circle centered at (0, 0)
        double d = r1 * r1 - x * x;
        if (d < 0) return 0.0;
        high = Math.min(high, Math.sqrt(Math.max(0, d)));

        // Circle centered at (a/2, sqrt(3)*a/2)
        double cx = a / 2.0;
        double cy = SQRT3 * a / 2.0;

        d = r2 * r2 - (x - cx) * (x - cx);
        if (d < 0) return 0.0;
        double s = Math.sqrt(Math.max(0, d));
        low = Math.max(low, cy - s);
        high = Math.min(high, cy + s);

        // Circle centered at (-a/2, sqrt(3)*a/2)
        d = r3 * r3 - (x + cx) * (x + cx);
        if (d < 0) return 0.0;
        s = Math.sqrt(Math.max(0, d));
        low = Math.max(low, cy - s);
        high = Math.min(high, cy + s);

        return Math.max(0.0, high - low);
    }

    static double area(double a, double r1, double r2, double r3) {
        double step = 2.0 * a / STEPS;
        double sum = height(-a, a, r1, r2, r3)
                   + height(a, a, r1, r2, r3);

        for (int i = 1; i < STEPS; i++) {
            double x = -a + i * step;
            sum += (i % 2 == 0 ? 2.0 : 4.0)
                 * height(x, a, r1, r2, r3);
        }

        return sum * step / 3.0;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        String first = fs.next();

        if (first == null) return;

        int T = Integer.parseInt(first);
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            double a = Double.parseDouble(fs.next());
            double r1 = Double.parseDouble(fs.next());
            double r2 = Double.parseDouble(fs.next());
            double r3 = Double.parseDouble(fs.next());

            out.append(String.format(Locale.US, "%.7f%n",
                    area(a, r1, r2, r3)));
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

        String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int c;

            do {
                c = read();
                if (c == -1) return null;
            } while (c <= ' ');

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }

            return sb.toString();
        }
    }
}

