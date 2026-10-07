import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            long a = Long.parseLong(st.nextToken());
            long k = Long.parseLong(st.nextToken());

            st = new StringTokenizer(br.readLine());

            long x1 = Long.parseLong(st.nextToken());
            long x2 = Long.parseLong(st.nextToken());
            long x3 = Long.parseLong(st.nextToken());

            long minX = Math.min(x1, Math.min(x2, x3));
            long maxX = Math.max(x1, Math.max(x2, x3));

            long spread = maxX - minX;

            // Movement can reduce the spread by at most 2K
            long remainingSpread = Math.max(0L, spread - 2L * k);

            // Maximum common horizontal width
            long width = Math.max(0L, a - remainingSpread);

            long area = width * a;

            out.append(String.format(Locale.US, "%.6f%n", (double) area));
        }

        System.out.print(out);
    }
}