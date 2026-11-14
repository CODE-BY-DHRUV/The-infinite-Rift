
import java.io.*;
import java.util.*;

public class Main {

    static class Node implements Comparable<Node> {
        int id;
        double dist;

        Node(int id, double dist) {
            this.id = id;
            this.dist = dist;
        }

        public int compareTo(Node other) {
            return Double.compare(this.dist, other.dist);
        }
    }

    static double hardness(double h1, double h2) {
        double diff = h1 - h2;
        double value = Math.sqrt(1.0 + diff * diff);

        if (h1 > h2) {
            return 0.5 + 0.5 * value;
        } else {
            return -0.5 + 1.5 * value;
        }
    }

    static double dijkstra(double[][] height, int r, int c,
                           int start, int end) {

        int n = r * c;

        double[] dist = new double[n];
        Arrays.fill(dist, Double.POSITIVE_INFINITY);

        PriorityQueue<Node> pq = new PriorityQueue<>();

        dist[start] = 0.0;
        pq.offer(new Node(start, 0.0));

        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        while (!pq.isEmpty()) {

            Node curr = pq.poll();

            int id = curr.id;
            double d = curr.dist;

            if (d > dist[id]) {
                continue;
            }

            if (id == end) {
                return d;
            }

            int row = id / c;
            int col = id % c;

            for (int k = 0; k < 4; k++) {

                int nr = row + dr[k];
                int nc = col + dc[k];

                if (nr < 0 || nr >= r || nc < 0 || nc >= c) {
                    continue;
                }

                int next = nr * c + nc;

                double cost = hardness(
                    height[row][col],
                    height[nr][nc]
                );

                double newDist = d + cost;

                if (newDist < dist[next]) {
                    dist[next] = newDist;
                    pq.offer(new Node(next, newDist));
                }
            }
        }

        return dist[end];
    }

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());

        for (int tc = 1; tc <= T; tc++) {

            StringTokenizer st = new StringTokenizer(br.readLine());

            int r = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());

            double[][] height = new double[r][c];

            for (int i = 0; i < r; i++) {

                st = new StringTokenizer(br.readLine());

                for (int j = 0; j < c; j++) {
                    height[i][j] = Double.parseDouble(st.nextToken());
                }
            }

            int q = Integer.parseInt(br.readLine().trim());

            System.out.println("Case " + tc + ":");

            for (int i = 0; i < q; i++) {

                st = new StringTokenizer(br.readLine());

                int is = Integer.parseInt(st.nextToken()) - 1;
                int js = Integer.parseInt(st.nextToken()) - 1;

                int ie = Integer.parseInt(st.nextToken()) - 1;
                int je = Integer.parseInt(st.nextToken()) - 1;

                int start = is * c + js;
                int end = ie * c + je;

                double ans = dijkstra(
                    height, r, c, start, end
                );

                System.out.printf(Locale.US, "%.6f%n", ans);
            }
        }
    }
}
