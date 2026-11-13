import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.Arrays;
import java.util.Collections;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        String line = br.readLine();
        if (line == null || line.trim().isEmpty()) return;
        int T = Integer.parseInt(line.trim());

        for (int t = 0; t < T; t++) {
            while (st == null || !st.hasMoreTokens()) {
                String l = br.readLine();
                if (l == null) return;
                st = new StringTokenizer(l);
            }
            int N = Integer.parseInt(st.nextToken());
            int M = Integer.parseInt(st.nextToken());

            int[] deg = new int[N + 1];
            for (int i = 0; i < M; i++) {
                while (st == null || !st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                int u = Integer.parseInt(st.nextToken());
                int v = Integer.parseInt(st.nextToken());
                deg[u]++;
                deg[v]++;
            }

            // Collect degrees and sort in descending order
            Integer[] d = new Integer[N];
            for (int i = 1; i <= N; i++) {
                d[i - 1] = deg[i];
            }
            Arrays.sort(d, Collections.reverseOrder());

            // Find m: largest 1-based index such that d[m-1] >= m - 1
            int m = 0;
            for (int i = 1; i <= N; i++) {
                if (d[i - 1] >= i - 1) {
                    m = i;
                } else {
                    break;
                }
            }

            // Calculate Left Hand Side (LHS)
            long lhs = 0;
            for (int i = 0; i < m; i++) {
                lhs += d[i];
            }

            // Calculate Right Hand Side (RHS)
            long rhs = (long) m * (m - 1);
            for (int i = m; i < N; i++) {
                rhs += Math.min(d[i], m);
            }

            if (lhs == rhs) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
}