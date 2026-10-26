import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;

public class Main {
    static final long INF = Long.MAX_VALUE / 4;

    static class Edge {
        int to, rev;
        long cap, flow, cost;
        Edge(int to, long cap, long cost, int rev) {
            this.to = to;
            this.cap = cap;
            this.flow = 0;
            this.cost = cost;
            this.rev = rev;
        }
    }

    static ArrayList<ArrayList<Edge>> graph;

    static void addEdge(int from, int to, long cap, long cost) {
        graph.get(from).add(new Edge(to, cap, cost, graph.get(to).size()));
        graph.get(to).add(new Edge(from, 0, -cost, graph.get(from).size() - 1));
    }

    static class MCMFResult {
        long flow, cost;
        MCMFResult(long flow, long cost) {
            this.flow = flow;
            this.cost = cost;
        }
    }

    static MCMFResult minCostMaxFlow(int n, int s, int t) {
        long totalFlow = 0;
        long totalCost = 0;
        long[] h = new long[n];
        long[] dist = new long[n];
        int[] parentEdge = new int[n];
        int[] parentNode = new int[n];

        while (true) {
            Arrays.fill(dist, INF);
            Arrays.fill(parentNode, -1);
            PriorityQueue<long[]> pq = new PriorityQueue<>((a, b) -> Long.compare(a[0], b[0]));

            dist[s] = 0;
            pq.add(new long[]{0, s});

            while (!pq.isEmpty()) {
                long[] curr = pq.poll();
                long d = curr[0];
                int u = (int) curr[1];

                if (d > dist[u]) continue;

                for (int i = 0; i < graph.get(u).size(); i++) {
                    Edge e = graph.get(u).get(i);
                    if (e.cap - e.flow > 0 && dist[u] + e.cost + h[u] - h[e.to] < dist[e.to]) {
                        dist[e.to] = dist[u] + e.cost + h[u] - h[e.to];
                        dist[e.to] = Math.max(dist[e.to], 0);
                        parentNode[e.to] = u;
                        parentEdge[e.to] = i;
                        pq.add(new long[]{dist[e.to], e.to});
                    }
                }
            }

            if (dist[t] == INF) break;

            for (int i = 0; i < n; i++) {
                if (dist[i] < INF) h[i] += dist[i];
            }

            long push = INF;
            int curr = t;
            while (curr != s) {
                int p = parentNode[curr];
                int idx = parentEdge[curr];
                Edge e = graph.get(p).get(idx);
                push = Math.min(push, e.cap - e.flow);
                curr = p;
            }

            curr = t;
            while (curr != s) {
                int p = parentNode[curr];
                int idx = parentEdge[curr];
                Edge e = graph.get(p).get(idx);
                e.flow += push;
                graph.get(e.to).get(e.rev).flow -= push;
                totalCost += push * e.cost;
                curr = p;
            }
            totalFlow += push;
        }

        return new MCMFResult(totalFlow, totalCost);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        String line = br.readLine();
        if (line == null) return;
        st = new StringTokenizer(line);
        int t = Integer.parseInt(st.nextToken());

        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {
            while (st == null || !st.hasMoreTokens()) {
                line = br.readLine();
                if (line == null) break;
                st = new StringTokenizer(line);
            }
            if (line == null) break;

            int n = Integer.parseInt(st.nextToken());
            int vCount = Integer.parseInt(st.nextToken());
            int wCount = Integer.parseInt(st.nextToken());

            int[] inDeg = new int[n + 1];
            int[] outDeg = new int[n + 1];

            for (int i = 0; i < vCount; i++) {
                while (!st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                int u = Integer.parseInt(st.nextToken());
                int w = Integer.parseInt(st.nextToken());
                outDeg[u]++;
                inDeg[w]++;
            }

            int[][] nonVital = new int[wCount][2];
            for (int i = 0; i < wCount; i++) {
                while (!st.hasMoreTokens()) {
                    st = new StringTokenizer(br.readLine());
                }
                int u = Integer.parseInt(st.nextToken());
                int w = Integer.parseInt(st.nextToken());
                nonVital[i][0] = u;
                nonVital[i][1] = w;
                outDeg[u]++;
                inDeg[w]++;
            }

            int S = 0;
            int T = n + 1;
            int totalNodes = n + 2;

            graph = new ArrayList<>();
            for (int i = 0; i < totalNodes; i++) {
                graph.add(new ArrayList<>());
            }

            long totalSupply = 0;
            for (int i = 1; i <= n; i++) {
                int diff = outDeg[i] - inDeg[i];
                if (diff > 0) {
                    addEdge(S, i, diff, 0);
                    totalSupply += diff;
                } else if (diff < 0) {
                    addEdge(i, T, -diff, 0);
                }
            }

            for (int i = 0; i < wCount; i++) {
                addEdge(nonVital[i][0], nonVital[i][1], 1, 1);
            }

            MCMFResult result = minCostMaxFlow(totalNodes, S, T);

            if (result.flow < totalSupply) {
                sb.append("-1\n");
            } else {
                sb.append(result.cost).append("\n");
            }
        }
        System.out.print(sb.toString());
    }
}