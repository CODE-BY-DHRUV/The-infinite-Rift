import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {
            int n = fs.nextInt();
            long minX = fs.nextLong();
            long maxX = fs.nextLong();

            int parityW = 1;
            int parityB = 0;

            for (int i = 0; i < n; i++) {
                long w = fs.nextLong();
                long b = fs.nextLong();

                parityW = (int) ((w * parityW) % 2);
                parityB = (int) ((w * parityB + b) % 2);
            }

            long total = maxX - minX + 1;
            long even = 0;

            if (parityW == 0) {
                if (parityB == 0) {
                    even = total;
                }
            } else {
                long firstEven = minX;

                if ((firstEven + parityB) % 2 != 0) {
                    firstEven++;
                }

                if (firstEven <= maxX) {
                    even = (maxX - firstEven) / 2 + 1;
                }
            }

            long odd = total - even;
            out.append(even).append(' ').append(odd).append('\n');
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
            } while (c <= ' ' && c != -1);

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }

            return sb.toString();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        long nextLong() throws IOException {
            return Long.parseLong(next());
        }
    }
}