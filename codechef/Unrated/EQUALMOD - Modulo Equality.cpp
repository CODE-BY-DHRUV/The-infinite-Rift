
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());

            long[] a = new long[n];
            long[] b = new long[n];

            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
            }

            st = new StringTokenizer(br.readLine());
            long minB = Long.MAX_VALUE;

            for (int i = 0; i < n; i++) {
                b[i] = Long.parseLong(st.nextToken());
                minB = Math.min(minB, b[i]);
            }

            long[] events = new long[n];
            int count = 0;
            long answer = 0;

            final long BASE = 1_000_000L;

            for (int i = 0; i < n; i++) {
                long r = a[i] % b[i];

                if (r == 0) {
                    // Already has remainder zero.
                } else {
                    answer += b[i] - r;

                    if (r < minB) {
                        events[count++] = r * BASE + i;
                    }
                }
            }

            Arrays.sort(events, 0, count);

            long currentCost = answer;
            long previousRemainder = 0;
            int j = 0;

            while (j < count) {
                long r = events[j] / BASE;

                currentCost += (r - previousRemainder) * n;

                long reduction = 0;

                while (j < count && events[j] / BASE == r) {
                    int idx = (int) (events[j] % BASE);
                    reduction += b[idx];
                    j++;
                }

                currentCost -= reduction;
                answer = Math.min(answer, currentCost);
                previousRemainder = r;
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}

