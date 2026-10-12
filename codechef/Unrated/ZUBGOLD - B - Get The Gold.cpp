
import java.io.*;

public class Main {

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

        double nextDouble() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);

            StringBuilder sb = new StringBuilder();
            if (c == '-') {
                sb.append((char) c);
                c = read();
            }

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }

            return Double.parseDouble(sb.toString());
        }

        int nextInt() throws IOException {
            return (int) nextDouble();
        }
    }

    static double[] subtract(double[] a, double[] b) {
        return new double[]{
            a[0] - b[0],
            a[1] - b[1],
            a[2] - b[2]
        };
    }

    static double[] cross(double[] a, double[] b) {
        return new double[]{
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]
        };
    }

    static double dot(double[] a, double[] b) {
        return a[0] * b[0]
             + a[1] * b[1]
             + a[2] * b[2];
    }

    static double[] add(double[] a, double[] b) {
        return new double[]{
            a[0] + b[0],
            a[1] + b[1],
            a[2] + b[2]
        };
    }

    static double[] scale(double[] a, double k) {
        return new double[]{
            a[0] * k,
            a[1] * k,
            a[2] * k
        };
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        for (int tc = 0; tc < T; tc++) {
            double[] S = {
                fs.nextDouble(),
                fs.nextDouble(),
                fs.nextDouble()
            };

            double[] A = {
                fs.nextDouble(),
                fs.nextDouble(),
                fs.nextDouble()
            };

            double[] B = {
                fs.nextDouble(),
                fs.nextDouble(),
                fs.nextDouble()
            };

            double[] u = subtract(A, S);
            double[] v = subtract(B, S);

            // Normal vector to the plane
            double[] n = cross(u, v);

            // Vector from S toward the origin
            double[] toOrigin = scale(S, -1.0);

            // Orient the normal toward the origin
            if (dot(n, toOrigin) < 0) {
                n = scale(n, -1.0);
            }

            // Normalize the normal vector
            double norm = Math.sqrt(dot(n, n));
            n = scale(n, 1.0 / norm);

            // Right turn from SA and left turn from SB
            double[] rightA = cross(n, u);
            double[] leftB = cross(n, v);

            double[] C = add(S, subtract(u, rightA));
            double[] D = add(S, add(v, leftB));

            // Gold is the midpoint of C and D
            double[] gold = scale(add(C, D), 0.5);

            out.append(String.format(
                java.util.Locale.US,
                "%.8f %.8f %.8f%n",
                gold[0], gold[1], gold[2]
            ));
        }

        System.out.print(out);
    }
}

