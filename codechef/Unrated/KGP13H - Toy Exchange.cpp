
import java.util.*;

public class Main {

    static class Edge {
        int to, rev, cap;

        Edge(int to, int rev, int cap) {
            this.to = to;
            this.rev = rev;
            this.cap = cap;
        }
    }

    static class Dinic {
        ArrayList<Edge>[] graph;
        int[] level, ptr;
        int n;

        @SuppressWarnings("unchecked")
        Dinic(int n) {
            this.n = n;
            graph = new ArrayList[n];

            for (int i = 0; i < n; i++) {
                graph[i] = new ArrayList<>();
            }

            level = new int[n];
            ptr = new int[n];
        }

        void addEdge(int u, int v, int cap) {
            Edge a = new Edge(v, graph[v].size(), cap);
            Edge b = new Edge(u, graph[u].size(), 0);

            graph[u].add(a);
            graph[v].add(b);
        }

        boolean bfs(int s, int t) {
            Arrays.fill(level, -1);

            Queue<Integer> q = new ArrayDeque<>();
            q.add(s);
            level[s] = 0;

            while (!q.isEmpty()) {
                int u = q.poll();

                for (Edge e : graph[u]) {
                    if (e.cap > 0 && level[e.to] == -1) {
                        level[e.to] = level[u] + 1;
                        q.add(e.to);
                    }
                }
            }

            return level[t] != -1;
        }

        int dfs(int u, int t, int pushed) {
            if (pushed == 0) return 0;
            if (u == t) return pushed;

            for (; ptr[u] < graph[u].size(); ptr[u]++) {

                Edge e = graph[u].get(ptr[u]);

                if (e.cap <= 0 ||
                    level[e.to] != level[u] + 1) {
                    continue;
                }

                int tr = dfs(e.to, t,
                        Math.min(pushed, e.cap));

                if (tr == 0) continue;

                e.cap -= tr;
                graph[e.to].get(e.rev).cap += tr;

                return tr;
            }

            return 0;
        }

        int maxFlow(int s, int t) {
            int flow = 0;

            while (bfs(s, t)) {
                Arrays.fill(ptr, 0);

                while (true) {
                    int pushed = dfs(s, t, Integer.MAX_VALUE);

                    if (pushed == 0) break;

                    flow += pushed;
                }
            }

            return flow;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();

        for (int tc = 1; tc <= N; tc++) {

            int K = sc.nextInt();
            int M = sc.nextInt();

            long[] sumana = new long[K];

            int distinct = 0;

            for (int i = 0; i < K; i++) {
                sumana[i] = sc.nextLong();

                if (sumana[i] > 0) {
                    distinct++;
                }
            }

            long[][] friends = new long[M][K];

            for (int i = 0; i < M; i++) {
                for (int j = 0; j < K; j++) {
                    friends[i][j] = sc.nextLong();
                }
            }

            // Node numbering
            int S = 0;
            int typeStart = 1;
            int friendStart = K + 1;
            int T = K + M + 1;

            Dinic dinic = new Dinic(T + 1);

            // Source -> Type nodes
            for (int i = 0; i < K; i++) {

                long extra = Math.max(0, sumana[i] - 1);

                int capacity = (int) Math.min(extra, K);

                if (capacity > 0) {
                    dinic.addEdge(S, typeStart + i, capacity);
                }
            }

            // Type nodes -> Friend nodes
            for (int i = 0; i < K; i++) {

                for (int j = 0; j < M; j++) {

                    if (friends[j][i] <= 1) {

                        dinic.addEdge(
                            typeStart + i,
                            friendStart + j,
                            1
                        );
                    }
                }
            }

            // Friend nodes -> Type nodes
            for (int j = 0; j < M; j++) {

                for (int i = 0; i < K; i++) {

                    if (friends[j][i] >= 2) {

                        dinic.addEdge(
                            friendStart + j,
                            typeStart + i,
                            1
                        );
                    }
                }
            }

            // Missing types -> Sink
            for (int i = 0; i < K; i++) {

                if (sumana[i] == 0) {

                    dinic.addEdge(
                        typeStart + i,
                        T,
                        1
                    );
                }
            }

            int additional = dinic.maxFlow(S, T);

            System.out.println(
                "Case " + tc + ": " + (distinct + additional)
            );
        }

        sc.close();
    }
}
