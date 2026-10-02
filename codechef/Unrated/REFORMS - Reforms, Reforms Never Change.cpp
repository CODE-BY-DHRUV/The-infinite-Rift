
import java.io.*;
import java.util.*;

public class Main {

    static final int NONE = 0;
    static final int IN = 1;
    static final int OUT = 2;

    static final int INF = 1_000_000_000;

    static class Edge {
        int to;
        boolean originalForward;

        Edge(int to, boolean originalForward) {
            this.to = to;
            this.originalForward = originalForward;
        }
    }

    /*
        We want the edge u -> v in the final graph.

        State of a vertex:
        0 = no operation
        1 = make all incident edges IN
        2 = make all incident edges OUT

        For an edge whose original direction is u -> v:

        NONE -> NONE : works only if original direction is u -> v
        NONE -> IN   : works
        NONE -> OUT  : doesn't work

        IN -> NONE   : doesn't work
        IN -> IN     : works
        IN -> OUT    : doesn't work

        OUT -> NONE  : works
        OUT -> IN    : works
        OUT -> OUT   : works

        For both endpoints operated, the appropriate endpoint can
        be made the last operation when necessary.
    */
    static boolean possible(int su, int sv, boolean originalForward) {

        // Neither endpoint is operated.
        if (su == NONE && sv == NONE) {
            return originalForward;
        }

        // Only v is operated.
        if (su == NONE) {
            return sv == IN;
        }

        // Only u is operated.
        if (sv == NONE) {
            return su == OUT;
        }

        // Both endpoints are operated.
        // u=OUT can make u -> v if u is last.
        // v=IN can make u -> v if v is last.
        return su == OUT || sv == IN;
    }

    static int solve(int n, ArrayList<Edge>[] graph) {

        /*
            dist[v][state] =
            minimum number of operations needed to reach v
            with v having the given state.
        */
        int[][] dist = new int[n + 1][3];

        for (int i = 1; i <= n; i++) {
            Arrays.fill(dist[i], INF);
        }

        Deque<Integer> dq = new ArrayDeque<>();

        // City 1 can either remain unchanged or be operated once.
        dist[1][NONE] = 0;
        dist[1][IN] = 1;
        dist[1][OUT] = 1;

        dq.addFirst(1 * 3 + NONE);
        dq.addLast(1 * 3 + IN);
        dq.addLast(1 * 3 + OUT);

        while (!dq.isEmpty()) {

            int code = dq.pollFirst();

            int u = code / 3;
            int su = code % 3;

            int curDist = dist[u][su];

            for (Edge edge : graph[u]) {

                int v = edge.to;

                for (int sv = 0; sv < 3; sv++) {

                    if (!possible(su, sv, edge.originalForward)) {
                        continue;
                    }

                    int cost = (sv == NONE ? 0 : 1);

                    int newDist = curDist + cost;

                    if (newDist < dist[v][sv]) {

                        dist[v][sv] = newDist;

                        int nextCode = v * 3 + sv;

                        if (cost == 0) {
                            dq.addFirst(nextCode);
                        } else {
                            dq.addLast(nextCode);
                        }
                    }
                }
            }
        }

        int answer = Math.min(
            dist[n][NONE],
            Math.min(dist[n][IN], dist[n][OUT])
        );

        // IMPORTANT: unreachable => -1
        return answer == INF ? -1 : answer;
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);

        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {

            int n = fs.nextInt();
            int m = fs.nextInt();

            ArrayList<Edge>[] graph = new ArrayList[n + 1];

            for (int i = 1; i <= n; i++) {
                graph[i] = new ArrayList<>();
            }

            for (int i = 0; i < m; i++) {

                int u = fs.nextInt();
                int v = fs.nextInt();

                /*
                    Original road:

                        u -> v

                    From u to v:
                        originalForward = true

                    From v to u:
                        originalForward = false
                */
                graph[u].add(new Edge(v, true));
                graph[v].add(new Edge(u, false));
            }

            out.append(solve(n, graph)).append('\n');
        }

        System.out.print(out);
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




