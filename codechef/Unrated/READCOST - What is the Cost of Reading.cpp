import java.io.*;
import java.util.*;

public class Main {

    // Returns:
    // sum_{i=0}^{n-1} floor((a*i + b) / m)
    static long floorSum(long n, long m, long a, long b) {
        long ans = 0;

        while (true) {
            if (a >= m) {
                ans += (n - 1) * n * (a / m) / 2;
                a %= m;
            }

            if (b >= m) {
                ans += n * (b / m);
                b %= m;
            }

            long yMax = a * n + b;

            if (yMax < m) {
                break;
            }

            n = yMax / m;
            b = yMax % m;

            // Swap m and a
            long temp = m;
            m = a;
            a = temp;
        }

        return ans;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        while (true) {
            String line = br.readLine();

            if (line == null) {
                break;
            }

            line = line.trim();

            if (line.isEmpty()) {
                continue;
            }

            StringTokenizer st = new StringTokenizer(line);

            long n = Long.parseLong(st.nextToken());
            long m = Long.parseLong(st.nextToken());
            long x = Long.parseLong(st.nextToken());

            if (n == 0 && m == 0 && x == 0) {
                break;
            }

            /*
             * Cost of person i (0-indexed):
             *
             * floor((x + i*n) / m)
             *
             * Hence:
             *
             * answer = sum_{i=0}^{m-1} floor((n*i + x) / m)
             */

            long answer = floorSum(m, m, n, x);

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}
