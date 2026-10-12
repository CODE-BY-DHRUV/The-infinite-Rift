
import java.io.*;
import java.util.*;

public class Main {
    static final long MOD = 1_000_000_007L;

    static int upperBound(int[] arr, long target) {
        int left = 0;
        int right = arr.length;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        StringBuilder out = new StringBuilder();
        int T = Integer.parseInt(br.readLine().trim());

        for (int tc = 1; tc <= T; tc++) {
            StringTokenizer st =
                new StringTokenizer(br.readLine());

            long Kp = Long.parseLong(st.nextToken());
            long Ks = Long.parseLong(st.nextToken());
            long P = Kp * Ks;

            int N = Integer.parseInt(br.readLine().trim());

            int[] G = new int[N];
            int[] S = new int[N];

            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) {
                G[i] = Integer.parseInt(st.nextToken());
            }

            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) {
                S[i] = Integer.parseInt(st.nextToken());
            }

            Arrays.sort(G);
            Arrays.sort(S);

            long ans = 1;

            for (int i = 0; i < N; i++) {
                // Minimum scooter performance must be
                // strictly greater than P / G[i].
                long threshold = P / G[i];

                // Number of scooters with performance
                // strictly greater than the threshold.
                int eligible = N - upperBound(S, threshold);

                // The previous i guards have used i scooters.
                long choices = eligible - i;

                if (choices <= 0) {
                    ans = 0;
                    break;
                }

                ans = (ans * choices) % MOD;
            }

            out.append("Case ")
               .append(tc)
               .append(": ")
               .append(ans)
               .append('\n');
        }

        System.out.print(out);
    }
}
