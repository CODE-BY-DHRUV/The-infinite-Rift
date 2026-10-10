
import java.io.*;
import java.util.*;

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

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        String first = fs.next();
        if (first == null) return;

        int T = Integer.parseInt(first);

        while (T-- > 0) {
            int n = fs.nextInt();
            int E = fs.nextInt();

            int[] x = new int[n];
            int min = Integer.MAX_VALUE;
            int max = Integer.MIN_VALUE;
            int minIdx = -1, maxIdx = -1, exactIdx = -1;

            for (int i = 0; i < n; i++) {
                x[i] = fs.nextInt();

                if (x[i] < min) {
                    min = x[i];
                    minIdx = i;
                }
                if (x[i] > max) {
                    max = x[i];
                    maxIdx = i;
                }
                if (x[i] == E && exactIdx == -1) {
                    exactIdx = i;
                }
            }

            if (E < min || E > max) {
                out.append("-1\n");
                continue;
            }

            double[] p = new double[n];

            if (exactIdx != -1) {
                p[exactIdx] = 1.0;
            } else {
                p[minIdx] = (double) (max - E) / (max - min);
                p[maxIdx] = (double) (E - min) / (max - min);
            }

            for (int i = 0; i < n; i++) {
                if (i > 0) out.append(' ');
                out.append(String.format(Locale.US, "%.10f", p[i]));
            }
            out.append('\n');
        }

        System.out.print(out);
    }
}
