
import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder sb = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {

            int n = fs.nextInt();

            // Build the tree
            ArrayList<Integer>[] graph = new ArrayList[n + 1];

            for (int i = 1; i <= n; i++) {
                graph[i] = new ArrayList<>();
            }

            for (int i = 0; i < n - 1; i++) {
                int u = fs.nextInt();
                int v = fs.nextInt();

                graph[u].add(v);
                graph[v].add(u);
            }

            // Read dead Orcs
            int m = fs.nextInt();

            boolean[] dead = new boolean[n + 1];

            for (int i = 0; i < m; i++) {
                int x = fs.nextInt();
                dead[x] = true;
            }

            // Number of dead ancestors for each node
            int[] deadAncestors = new int[n + 1];

            boolean[] visited = new boolean[n + 1];

            int[] queue = new int[n];
            int front = 0, rear = 0;

            // Root the tree at node 1
            queue[rear++] = 1;
            visited[1] = true;

            double answer = 0.0;

            while (front < rear) {

                int u = queue[front++];

                // Probability that this Orc's roll-call is skipped
                int d = deadAncestors[u];

                answer += (double) d / (d + 1);

                for (int v : graph[u]) {

                    if (!visited[v]) {

                        visited[v] = true;

                        deadAncestors[v] = deadAncestors[u]
                                + (dead[u] ? 1 : 0);

                        queue[rear++] = v;
                    }
                }
            }

            sb.append(String.format(Locale.US, "%.10f", answer))
              .append('\n');
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

            int num = 0;

            while (c > ' ') {
                num = num * 10 + c - '0';
                c = read();
            }

            return num;
        }
    }
}
