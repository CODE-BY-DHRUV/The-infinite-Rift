import java.util.*;
import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine().trim());

        for (int tc = 1; tc <= T; tc++) {

            StringTokenizer st = new StringTokenizer(br.readLine());
            int N = Integer.parseInt(st.nextToken());
            int K = Integer.parseInt(st.nextToken());

            PriorityQueue<Long> pq = new PriorityQueue<>();

            st = new StringTokenizer(br.readLine());

            for (int i = 0; i < N; i++) {
                pq.offer(Long.parseLong(st.nextToken()));
            }

            // Padding with zeroes for K-way merging
            int rem = (N - 1) % (K - 1);

            if (rem != 0) {
                int extra = (K - 1) - rem;

                for (int i = 0; i < extra; i++) {
                    pq.offer(0L);
                }
            }

            long ans = 0;

            while (pq.size() > 1) {

                long sum = 0;

                // Merge K smallest files
                for (int i = 0; i < K; i++) {
                    sum += pq.poll();
                }

                ans += sum;
                pq.offer(sum);
            }

            System.out.println("Case " + tc + ": " + ans);
        }
    }
}
