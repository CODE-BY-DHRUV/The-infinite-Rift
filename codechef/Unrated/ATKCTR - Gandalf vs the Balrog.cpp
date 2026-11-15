
import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder sb = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {

            int n = fs.nextInt();
            int m = fs.nextInt();

            int[] degree = new int[n + 1];

            // Initially, attack i defeats i-1 attacks.
            for (int i = 1; i <= n; i++) {
                degree[i] = i - 1;
            }

            // Process anomalous pairs.
            for (int i = 0; i < m; i++) {

                int x = fs.nextInt();
                int y = fs.nextInt();

                degree[x]++;
                degree[y]--;
            }

            int answer = -1;

            // Find an attack that defeats every other attack.
            for (int i = 1; i <= n; i++) {

                if (degree[i] == n - 1) {
                    answer = i;
                    break;
                }
            }

            if (answer != -1) {
                sb.append("2 ").append(answer).append('\n');
            } else {
                sb.append("1").append('\n');
            }
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

                if (len <= 0) {
                    return -1;
                }
            }

            return buffer[ptr++];
        }

        int nextInt() throws IOException {

            int c;

            do {
                c = read();
            } while (c <= ' ' && c != -1);

            int sign = 1;

            if (c == '-') {
                sign = -1;
                c = read();
            }

            int num = 0;

            while (c > ' ') {
                num = num * 10 + c - '0';
                c = read();
            }

            return num * sign;
        }
    }
}

