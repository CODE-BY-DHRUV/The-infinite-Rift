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

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            long sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            long res = 0;
            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }
            return res * sign;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();

        int n = fs.nextInt();
        long R = fs.nextLong();

        long[] a = new long[n];

        for (int i = 0; i < n; i++) {
            a[i] = fs.nextLong();
        }

        Arrays.sort(a);

        long prefix = 0;
        long answer = Long.MAX_VALUE;

        for (int s = 1; s <= n; s++) {
            prefix += a[s - 1];

            // floor(prefix / s) + (n - s) * R
            long possible = prefix / s + (long) (n - s) * R;

            answer = Math.min(answer, possible);
        }

        System.out.println(answer);
    }
}