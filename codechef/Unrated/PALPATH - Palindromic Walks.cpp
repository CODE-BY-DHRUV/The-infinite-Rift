import java.io.*;
import java.util.*;

public class Main {

    static class Edge {
        int to;
        long weight;
        char ch;

        Edge(int to, long weight, char ch) {
            this.to = to;
            this.weight = weight;
            this.ch = ch;
        }
    }

    static class State implements Comparable<State> {
        int u, v;
        long dist;

        State(int u, int v, long dist) {
            this.u = u;
            this.v = v;
            this.dist = dist;
        }

        @Override
        public int compareTo(State other) {
            return Long.compare(this.dist, other.dist);
        }
    }

    static final long INF = Long.MAX_VALUE / 4;

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();
            int m = fs.nextInt();
            int s = fs.nextInt() - 1;
            int t = fs.nextInt() - 1;

            @SuppressWarnings("unchecked")
            ArrayList<Edge>[] graph = new ArrayList[n];

            for (int i = 0; i < n; i++) {
                graph[i] = new ArrayList<>();
            }

            // Minimum weight of an edge between two vertices.
            long[][] minEdge = new long[n][n];

            for (int i = 0; i < n; i++) {
                Arrays.fill(minEdge[i], INF);
            }

            for (int i = 0; i < m; i++) {

                int u = fs.nextInt() - 1;
                int v = fs.nextInt() - 1;
                long w = fs.nextLong();
                char c = fs.nextChar();

                graph[u].add(new Edge(v, w, c));
                graph[v].add(new Edge(u, w, c));

                minEdge[u][v] = Math.min(minEdge[u][v], w);
                minEdge[v][u] = Math.min(minEdge[v][u], w);
            }

            /*
             * dist[u][v] =
             * minimum cost of choosing matching characters
             * from the two ends, starting at (s,t)
             * and reaching (u,v).
             */
            long[][] dist = new long[n][n];

            for (int i = 0; i < n; i++) {
                Arrays.fill(dist[i], INF);
            }

            PriorityQueue<State> pq = new PriorityQueue<>();

            dist[s][t] = 0;
            pq.offer(new State(s, t, 0));

            long answer = INF;

            while (!pq.isEmpty()) {

                State cur = pq.poll();

                int u = cur.u;
                int v = cur.v;
                long d = cur.dist;

                if (d != dist[u][v]) {
                    continue;
                }

                /*
                 * Even length palindrome:
                 *
                 * The two constructed halves meet at
                 * the same vertex.
                 */
                if (u == v) {
                    answer = Math.min(answer, d);
                }

                /*
                 * Odd length palindrome:
                 *
                 * One edge between u and v can become
                 * the middle character.
                 */
                if (minEdge[u][v] != INF) {
                    answer = Math.min(answer, d + minEdge[u][v]);
                }

                /*
                 * Add one character to each side.
                 *
                 * The characters must be equal.
                 */
                for (Edge e1 : graph[u]) {

                    for (Edge e2 : graph[v]) {

                        if (e1.ch != e2.ch) {
                            continue;
                        }

                        int nu = e1.to;
                        int nv = e2.to;

                        long nd = d + e1.weight + e2.weight;

                        if (nd < dist[nu][nv]) {
                            dist[nu][nv] = nd;
                            pq.offer(new State(nu, nv, nd));
                        }
                    }
                }
            }

            if (answer == INF) {
                out.append("-1\n");
            } else {
                out.append(answer).append('\n');
            }
        }

        System.out.print(out);
    }

    // Fast input
    static class FastScanner {

        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        FastScanner(InputStream is) {
            in = is;
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

        String next() throws IOException {

            StringBuilder sb = new StringBuilder();
            int c;

            do {
                c = read();
            } while (c <= ' ');

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }

            return sb.toString();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        char nextChar() throws IOException {
            return next().charAt(0);
        }
    }
}
