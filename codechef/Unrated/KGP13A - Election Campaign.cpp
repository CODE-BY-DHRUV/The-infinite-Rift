
import java.io.*;
import java.util.*;

public class Main {

    static class Edge {
        int to;
        long weight;

        Edge(int to, long weight) {
            this.to = to;
            this.weight = weight;
        }
    }

    static class Node implements Comparable<Node> {
        int vertex;
        long dist;

        Node(int vertex, long dist) {
            this.vertex = vertex;
            this.dist = dist;
        }

        public int compareTo(Node other) {
            return Long.compare(this.dist, other.dist);
        }
    }

    static ArrayList<Edge>[] graph;
    static int K;

    // Find the unique path from source to destination.
    static boolean[] findPath(int source, int destination) {

        int[] parent = new int[K];
        Arrays.fill(parent, -1);

        long[] parentWeight = new long[K];

        Stack<Integer> stack = new Stack<>();
        stack.push(source);

        parent[source] = source;

        while (!stack.isEmpty()) {

            int u = stack.pop();

            if (u == destination) {
                break;
            }

            for (Edge e : graph[u]) {

                int v = e.to;

                if (parent[v] == -1) {

                    parent[v] = u;
                    parentWeight[v] = e.weight;

                    stack.push(v);
                }
            }
        }

        // Mark all vertices belonging to the path.
        boolean[] onPath = new boolean[K];

        int current = destination;

        while (current != source) {

            onPath[current] = true;
            current = parent[current];
        }

        onPath[source] = true;

        return onPath;
    }

    // Multi-source Dijkstra.
    static long calculateCost(boolean[] onPath) {

        long INF = Long.MAX_VALUE / 4;

        long[] dist = new long[K];
        Arrays.fill(dist, INF);

        PriorityQueue<Node> pq = new PriorityQueue<>();

        // Every vertex on the selected path is a source.
        for (int i = 0; i < K; i++) {

            if (onPath[i]) {

                dist[i] = 0;
                pq.offer(new Node(i, 0));
            }
        }

        while (!pq.isEmpty()) {

            Node node = pq.poll();

            int u = node.vertex;
            long d = node.dist;

            if (d != dist[u]) {
                continue;
            }

            for (Edge e : graph[u]) {

                int v = e.to;
                long newDist = d + e.weight;

                if (newDist < dist[v]) {

                    dist[v] = newDist;

                    pq.offer(
                        new Node(v, newDist)
                    );
                }
            }
        }

        // Sum distances from all villages to the path.
        long total = 0;

        for (int i = 0; i < K; i++) {
            total += dist[i];
        }

        return total;
    }

    static long solve(ArrayList<Integer> connected) {

        long answer = Long.MAX_VALUE;

        int M = connected.size();

        // Try every possible pair of endpoints.
        for (int i = 0; i < M; i++) {

            for (int j = i; j < M; j++) {

                int u = connected.get(i);
                int v = connected.get(j);

                // Find the unique path.
                boolean[] onPath = findPath(u, v);

                // Calculate total distance to this path.
                long cost = calculateCost(onPath);

                answer = Math.min(answer, cost);
            }
        }

        return answer;
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);

        StringBuilder sb = new StringBuilder();

        int T = fs.nextInt();

        for (int tc = 1; tc <= T; tc++) {

            K = fs.nextInt();

            graph = new ArrayList[K];

            for (int i = 0; i < K; i++) {
                graph[i] = new ArrayList<>();
            }

            ArrayList<Integer> connected = new ArrayList<>();

            // Read village information.
            for (int i = 0; i < K; i++) {

                int F = fs.nextInt();
                int D = fs.nextInt();

                if (F == 1) {
                    connected.add(i);
                }

                for (int j = 0; j < D; j++) {

                    int v = fs.nextInt() - 1;
                    long w = fs.nextLong();

                    graph[i].add(new Edge(v, w));
                }
            }

            long answer = solve(connected);

            sb.append("Case ")
              .append(tc)
              .append(": ")
              .append(answer)
              .append('\n');
        }

        System.out.print(sb);
    }

    static class FastScanner {

        BufferedReader br;
        StringTokenizer st;

        FastScanner(InputStream in) {
            br = new BufferedReader(
                new InputStreamReader(in)
            );
        }

        String next() throws IOException {

            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }

            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        long nextLong() throws IOException {
            return Long.parseLong(next());
        }
    }
}
