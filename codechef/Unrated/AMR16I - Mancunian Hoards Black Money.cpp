import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            long S = Long.parseLong(st.nextToken());
            int N = Integer.parseInt(st.nextToken());
            long X = Long.parseLong(st.nextToken());

            long[] c = new long[N];
            st = new StringTokenizer(br.readLine());

            for (int i = 0; i < N; i++) {
                c[i] = Long.parseLong(st.nextToken());
            }

            long[] piles = new long[N + 1];
            piles[0] = S;

            long sum = S;

            for (int i = 0; i < N; i++) {
                if (sum > X || c[i] > X - sum) {
                    piles[i + 1] = X + 1;
                } else {
                    piles[i + 1] = sum + c[i];
                }

                if (piles[i + 1] > X || sum > X - piles[i + 1]) {
                    sum = X + 1;
                } else {
                    sum += piles[i + 1];
                }
            }

            long remaining = X;

            for (int i = N; i >= 0; i--) {
                if (piles[i] <= remaining) {
                    remaining -= piles[i];
                }
            }

            out.append(remaining == 0 ? "yes" : "no").append('\n');
        }

        System.out.print(out);
    }
}