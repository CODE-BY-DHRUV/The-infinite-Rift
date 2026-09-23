import java.io.*;
import java.util.*;

public class Main {

    static int n, m;
    static ArrayList<Integer>[] graph;

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);

        n = fs.nextInt();
        m = fs.nextInt();

        graph = new ArrayList[n];

        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }

        // Polygon edges
        for (int i = 0; i < n; i++) {
            int u = i;
            int v = (i + 1) % n;

            graph[u].add(v);
            graph[v].add(u);
        }

        // Chords
        for (int i = 0; i < m; i++) {
            int x = fs.nextInt() - 1;
            int y = fs.nextInt() - 1;

            graph[x].add(y);
            graph[y].add(x);
        }

        // First check if graph is bipartite.
        int[] color = new int[n];

        if (isBipartite(color)) {
            StringBuilder sb = new StringBuilder();

            sb.append(2).append('\n');

            for (int i = 0; i < n; i++) {
                sb.append(color[i]);
                if (i + 1 < n) sb.append(' ');
            }

            sb.append('\n');

            System.out.print(sb);
            return;
        }

        // Not bipartite => minimum is 3.
        int[] answer = threeColor();

        StringBuilder sb = new StringBuilder();

        sb.append(3).append('\n');

        for (int i = 0; i < n; i++) {
            sb.append(answer[i]);
            if (i + 1 < n) sb.append(' ');
        }

        sb.append('\n');

        System.out.print(sb);
    }

    // Check whether graph is bipartite.
    static boolean isBipartite(int[] color) {
        Arrays.fill(color, 0);

        Queue<Integer> queue = new ArrayDeque<>();

        for (int start = 0; start < n; start++) {
            if (color[start] != 0) continue;

            color[start] = 1;
            queue.offer(start);

            while (!queue.isEmpty()) {
                int u = queue.poll();

                for (int v : graph[u]) {
                    if (color[v] == 0) {
                        color[v] = 3 - color[u];
                        queue.offer(v);
                    } else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    // Since the graph is outerplanar, it is 2-degenerate.
    // Remove vertices of degree <= 2, then color in reverse order.
    static int[] threeColor() {

        int[] degree = new int[n];

        for (int i = 0; i < n; i++) {
            degree[i] = graph[i].size();
        }

        boolean[] removed = new boolean[n];

        ArrayDeque<Integer> queue = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            if (degree[i] <= 2) {
                queue.offer(i);
            }
        }

        int[] order = new int[n];
        int count = 0;

        while (!queue.isEmpty()) {
            int u = queue.poll();

            if (removed[u]) continue;

            removed[u] = true;
            order[count++] = u;

            for (int v : graph[u]) {
                if (!removed[v]) {
                    degree[v]--;

                    if (degree[v] <= 2) {
                        queue.offer(v);
                    }
                }
            }
        }

        int[] color = new int[n];

        // Reverse removal order.
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];

            boolean used1 = false;
            boolean used2 = false;
            boolean used3 = false;

            for (int v : graph[u]) {
                if (color[v] == 1) used1 = true;
                if (color[v] == 2) used2 = true;
                if (color[v] == 3) used3 = true;
            }

            if (!used1) {
                color[u] = 1;
            } else if (!used2) {
                color[u] = 2;
            } else {
                color[u] = 3;
            }
        }

        return color;
    }

    // Fast input
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        FastScanner(InputStream is) {
            in = is;
        }

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;

                if (len <= 0) return -1;
            }

            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            int sign = 1;

            if (c == '-') {
                sign = -1;
                c = read();
            }

            int result = 0;

            while (c > ' ') {
                result = result * 10 + (c - '0');
                c = read();
            }

            return result * sign;
        }
    }
}
