import java.io.*;
import java.util.*;

public class Main {

    static class Point {
        long x, y;

        Point(long x, long y) {
            this.x = x;
            this.y = y;
        }
    }

    static class Polygon {
        Point[] p;

        Polygon(Point[] p) {
            this.p = p;
        }
    }

    // Cross product:
    // (b-a) x (c-a)
    static long cross(Point a, Point b, Point c) {
        return (b.x - a.x) * (c.y - a.y)
             - (b.y - a.y) * (c.x - a.x);
    }

    // Returns true if point p is strictly inside convex polygon poly.
    // Polygon vertices are given counter-clockwise.
    static boolean strictlyInside(Point p, Polygon poly) {
        Point[] a = poly.p;
        int n = a.length;

        // Vertex itself is not strictly inside.
        for (int i = 0; i < n; i++) {
            if (p.x == a[i].x && p.y == a[i].y) {
                return false;
            }
        }

        // p must lie between rays v0->v1 and v0->v(n-1).
        long c1 = cross(a[0], a[1], p);
        long c2 = cross(a[0], a[n - 1], p);

        if (c1 <= 0 || c2 >= 0) {
            return false;
        }

        // Find sector:
        // a[lo] and a[lo+1] contain p relative to a[0].
        int lo = 1;
        int hi = n - 1;

        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;

            if (cross(a[0], a[mid], p) >= 0) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        // p must be strictly to the left of edge lo -> lo+1.
        return cross(a[lo], a[lo + 1], p) > 0;
    }

    // Returns true if polygon A is strictly inside polygon B.
    static boolean containsStrictly(Polygon A, Polygon B) {
        for (Point p : A.p) {
            if (!strictlyInside(p, B)) {
                return false;
            }
        }
        return true;
    }

    /*
     * Bipartite maximum matching.
     *
     * Left side  = polygons 0...N-1
     * Right side = polygons 0...N-1
     *
     * Edge A -> B exists when A is strictly inside B.
     */
    static int maxMatching(ArrayList<Integer>[] graph, int n) {
        int[] matchRight = new int[n];
        Arrays.fill(matchRight, -1);

        int result = 0;

        for (int u = 0; u < n; u++) {
            boolean[] visited = new boolean[n];

            if (dfs(u, graph, matchRight, visited)) {
                result++;
            }
        }

        return result;
    }

    static boolean dfs(
            int u,
            ArrayList<Integer>[] graph,
            int[] matchRight,
            boolean[] visited) {

        for (int v : graph[u]) {

            if (visited[v]) {
                continue;
            }

            visited[v] = true;

            if (matchRight[v] == -1 ||
                dfs(matchRight[v], graph, matchRight, visited)) {

                matchRight[v] = u;
                return true;
            }
        }

        return false;
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);

        int T = fs.nextInt();

        StringBuilder out = new StringBuilder();

        while (T-- > 0) {

            int N = fs.nextInt();

            Polygon[] polygons = new Polygon[N];

            for (int i = 0; i < N; i++) {

                int V = fs.nextInt();

                Point[] points = new Point[V];

                for (int j = 0; j < V; j++) {
                    long x = fs.nextLong();
                    long y = fs.nextLong();

                    points[j] = new Point(x, y);
                }

                polygons[i] = new Polygon(points);
            }

            // Build containment DAG.
            ArrayList<Integer>[] graph = new ArrayList[N];

            for (int i = 0; i < N; i++) {
                graph[i] = new ArrayList<>();
            }

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {

                    if (i == j) {
                        continue;
                    }

                    // i is strictly inside j
                    if (containsStrictly(polygons[i], polygons[j])) {
                        graph[i].add(j);
                    }
                }
            }

            /*
             * Dilworth's theorem:
             *
             * maximum antichain =
             * N - maximum matching
             */
            int matching = maxMatching(graph, N);

            int answer = N - matching;

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }

    // Fast input
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

        long nextLong() throws IOException {

            int c;

            do {
                c = read();
            } while (c <= ' ');

            boolean negative = false;

            if (c == '-') {
                negative = true;
                c = read();
            }

            long result = 0;

            while (c > ' ') {
                result = result * 10 + (c - '0');
                c = read();
            }

            return negative ? -result : result;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}
