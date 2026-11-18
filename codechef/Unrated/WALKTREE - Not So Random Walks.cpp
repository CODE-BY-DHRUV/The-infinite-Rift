
import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());

        StringBuilder ans = new StringBuilder();

        while (T-- > 0) {

            int n = Integer.parseInt(br.readLine().trim());

            int[][] children = new int[n + 1][];
            int[] k = new int[n + 1];

            for (int i = 1; i <= n; i++) {

                StringTokenizer st =
                    new StringTokenizer(br.readLine());

                k[i] = Integer.parseInt(st.nextToken());

                children[i] = new int[k[i]];

                for (int j = 0; j < k[i]; j++) {
                    children[i][j] =
                        Integer.parseInt(st.nextToken());
                }
            }

            long[] A = new long[n + 1];
            long[] B = new long[n + 1];

            // Root initialization
            A[1] = 1;
            B[1] = 1;

            // Iterative BFS
            int[] queue = new int[n + 1];

            int front = 0;
            int rear = 0;

            queue[rear++] = 1;

            while (front < rear) {

                int u = queue[front++];

                for (int j = 0; j < k[u]; j++) {

                    int v = children[u][j];

                    // First visit of child
                    A[v] = (A[u] + B[u] * j) % MOD;

                    // Difference between consecutive visits
                    B[v] = (B[u] * k[u]) % MOD;

                    queue[rear++] = v;
                }
            }

            // Output first visit iteration of each node
            for (int i = 1; i <= n; i++) {

                ans.append(A[i]);

                if (i < n) {
                    ans.append(" ");
                }
            }

            ans.append('\n');
        }

        System.out.print(ans);
    }
}
