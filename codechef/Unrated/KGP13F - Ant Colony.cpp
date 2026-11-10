
import java.io.*;
import java.util.*;

public class Main {

    static long gcd(long a, long b) {
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder sb = new StringBuilder();

        int T = fs.nextInt();

        for (int tc = 1; tc <= T; tc++) {

            long[] x = new long[4];
            long[] y = new long[4];

            // Read four vertices
            for (int i = 0; i < 4; i++) {
                x[i] = fs.nextLong();
                y[i] = fs.nextLong();
            }

            long area2 = 0;
            long boundary = 0;

            for (int i = 0; i < 4; i++) {

                int j = (i + 1) % 4;

                // Shoelace formula (twice the area)
                area2 += x[i] * y[j] - y[i] * x[j];

                // Boundary lattice points
                long dx = Math.abs(x[j] - x[i]);
                long dy = Math.abs(y[j] - y[i]);

                boundary += gcd(dx, dy);
            }

            area2 = Math.abs(area2);

            // Pick's theorem:
            // Total points = Area + Boundary / 2 + 1

            long answer = (area2 + boundary) / 2 + 1;

            sb.append("Case ")
              .append(tc)
              .append(": ")
              .append(answer)
              .append('\n');
        }

        System.out.print(sb);
    }

    static class FastScanner {

        BufferedReader br;
        StringTokenizer st;

        FastScanner(InputStream in) {
            br = new BufferedReader(
                new InputStreamReader(in)
            );
        }

        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }

        long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
}

