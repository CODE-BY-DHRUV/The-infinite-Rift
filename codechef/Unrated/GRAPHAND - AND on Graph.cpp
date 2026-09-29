import java.io.*;
import java.util.*;

public class Main {

    static class Edge {
        int to;
        long cost;
        int value;

        Edge(int to, long cost, int value) {
            this.to = to;
            this.cost = cost;
            this.value = value;
        }
    }

    static class State implements Comparable<State> {
        int node;
        long dist;

        State(int node, long dist) {
            this.node = node;
            this.dist = dist;
        }

        @Override
        public int compareTo(State other) {
            return Long.compare(this.dist, other.dist);
        }
    }

    static int n;
    static ArrayList<Edge>[] graph;

    static long dijkstra(int s, int t, int mask) {
        long INF = Long.MAX_VALUE / 4;

        long[] dist = new long[n + 1];
        Arrays.fill(dist, INF);

        PriorityQueue<State> pq = new PriorityQueue<>();

        dist[s] = 0;
        pq.add(new State(s, 0));

        while (!pq.isEmpty()) {
            State cur = pq.poll();

            int u = cur.node;
            long d = cur.dist;

            if (d != dist[u]) {
                continue;
            }

            if (u == t) {
                return d;
            }

            for (Edge e : graph[u]) {

                // This edge must contain every bit in mask.
                if ((e.value & mask) != mask) {
                    continue;
                }

                int v = e.to;
                long nd = d + e.cost;

                if (nd < dist[v]) {
                    dist[v] = nd;
                    pq.add(new State(v, nd));
                }
            }
        }

        return INF;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st = new StringTokenizer(br.readLine());

        n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());

        graph = new ArrayList[n + 1];

        for (int i = 1; i <= n; i++) {
            graph[i] = new ArrayList<>();
        }

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());

            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            long c = Long.parseLong(st.nextToken());
            int v = Integer.parseInt(st.nextToken());

            graph[a].add(new Edge(b, c, v));
            graph[b].add(new Edge(a, c, v));
        }

        st = new StringTokenizer(br.readLine());

        int s = Integer.parseInt(st.nextToken());
        int t = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());

        long answer = Long.MAX_VALUE / 4;

        /*
         * Case 1:
         * AND of the walk is exactly K.
         *
         * Every edge must contain all 1-bits of K.
         */
        long result = dijkstra(s, t, K);
        answer = Math.min(answer, result);

        /*
         * Case 2:
         * AND > K.
         *
         * Let i be the highest differing bit.
         * K[i] = 0 and AND[i] = 1.
         *
         * Every edge must contain:
         *   - all 1-bits of K above i
         *   - bit i
         */
        for (int i = 30; i >= 0; i--) {

            // Only zero bits of K can be the first differing bit.
            if ((K & (1 << i)) != 0) {
                continue;
            }

            // Keep bits above i from K.
            int higherBits = K & ~((1 << (i + 1)) - 1);

            // Force bit i to be 1.
            int mask = higherBits | (1 << i);

            result = dijkstra(s, t, mask);
            answer = Math.min(answer, result);
        }

        if (answer == Long.MAX_VALUE / 4) {
            System.out.println(-1);
        } else {
            System.out.println(answer);
        }
    }
}