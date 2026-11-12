
import java.io.*;
import java.util.*;

public class Main {

    static class Point {
        double x, y;

        Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    }

    static class Triangle {
        int a, b, c;
        double cx, cy, r2;
        boolean valid = true;

        Triangle(int a, int b, int c, Point[] p) {
            this.a = a;
            this.b = b;
            this.c = c;

            Point A = p[a];
            Point B = p[b];
            Point C = p[c];

            double d = 2.0 * (
                A.x * (B.y - C.y) +
                B.x * (C.y - A.y) +
                C.x * (A.y - B.y)
            );

            if (Math.abs(d) < 1e-12) {
                valid = false;
                return;
            }

            double aa = A.x * A.x + A.y * A.y;
            double bb = B.x * B.x + B.y * B.y;
            double cc = C.x * C.x + C.y * C.y;

            cx = (
                aa * (B.y - C.y) +
                bb * (C.y - A.y) +
                cc * (A.y - B.y)
            ) / d;

            cy = (
                aa * (C.x - B.x) +
                bb * (A.x - C.x) +
                cc * (B.x - A.x)
            ) / d;

            double dx = cx - A.x;
            double dy = cy - A.y;

            r2 = dx * dx + dy * dy;
        }

        boolean contains(Point p) {
            double dx = p.x - cx;
            double dy = p.y - cy;

            double dist2 = dx * dx + dy * dy;

            return dist2 <= r2 + 1e-9 * Math.max(1.0, r2);
        }

        boolean isAcute(Point[] p) {
            Point A = p[a];
            Point B = p[b];
            Point C = p[c];

            double ab = (A.x - B.x) * (A.x - B.x)
                      + (A.y - B.y) * (A.y - B.y);

            double bc = (B.x - C.x) * (B.x - C.x)
                      + (B.y - C.y) * (B.y - C.y);

            double ca = (C.x - A.x) * (C.x - A.x)
                      + (C.y - A.y) * (C.y - A.y);

            return ab + bc > ca &&
                   bc + ca > ab &&
                   ca + ab > bc;
        }
    }

    static class Edge {
        int u, v, count;

        Edge(int u, int v) {
            this.u = u;
            this.v = v;
            this.count = 1;
        }
    }

    static long edgeKey(int u, int v) {
        int mn = Math.min(u, v);
        int mx = Math.max(u, v);

        return ((long) mn << 32) | (mx & 0xffffffffL);
    }

    static void addEdge(
        HashMap<Long, Edge> edges,
        int u, int v
    ) {
        long key = edgeKey(u, v);

        Edge e = edges.get(key);

        if (e == null) {
            edges.put(key, new Edge(u, v));
        } else {
            e.count++;
        }
    }

    static double solve(Point[] input) {

        int n = input.length;

        if (n < 3) return -1;

        // Remove duplicate points.
        ArrayList<Point> unique = new ArrayList<>();

        HashSet<String> seen = new HashSet<>();

        for (Point p : input) {
            String key = Double.toString(p.x) + "," +
                         Double.toString(p.y);

            if (seen.add(key)) {
                unique.add(p);
            }
        }

        n = unique.size();

        if (n < 3) return -1;

        // Randomized insertion order.
        Collections.shuffle(unique, new Random(1234567));

        double minX = Double.MAX_VALUE;
        double minY = Double.MAX_VALUE;
        double maxX = -Double.MAX_VALUE;
        double maxY = -Double.MAX_VALUE;

        for (Point p : unique) {
            minX = Math.min(minX, p.x);
            minY = Math.min(minY, p.y);
            maxX = Math.max(maxX, p.x);
            maxY = Math.max(maxY, p.y);
        }

        double midX = (minX + maxX) / 2.0;
        double midY = (minY + maxY) / 2.0;

        double d = Math.max(maxX - minX, maxY - minY);

        if (d == 0) return -1;

        // Super triangle.
        Point[] p = new Point[n + 3];

        for (int i = 0; i < n; i++) {
            p[i] = unique.get(i);
        }

        p[n] = new Point(midX - 20 * d, midY - 10 * d);
        p[n + 1] = new Point(midX + 20 * d, midY - 10 * d);
        p[n + 2] = new Point(midX, midY + 20 * d);

        ArrayList<Triangle> triangles = new ArrayList<>();

        triangles.add(new Triangle(n, n + 1, n + 2, p));

        // Bowyer-Watson algorithm.
        for (int i = 0; i < n; i++) {

            HashMap<Long, Edge> edges = new HashMap<>();

            ArrayList<Triangle> remaining = new ArrayList<>();

            Point current = p[i];

            for (Triangle t : triangles) {

                if (t.contains(current)) {

                    addEdge(edges, t.a, t.b);
                    addEdge(edges, t.b, t.c);
                    addEdge(edges, t.c, t.a);

                } else {
                    remaining.add(t);
                }
            }

            for (Edge e : edges.values()) {

                if (e.count == 1) {

                    Triangle nt = new Triangle(
                        e.u, e.v, i, p
                    );

                    if (nt.valid) {
                        remaining.add(nt);
                    }
                }
            }

            triangles = remaining;
        }

        // Find the largest circumcircle of an acute triangle.
        double best = -1;

        for (Triangle t : triangles) {

            // Ignore triangles involving super vertices.
            if (t.a >= n || t.b >= n || t.c >= n) {
                continue;
            }

            if (!t.isAcute(p)) {
                continue;
            }

            best = Math.max(best, t.r2);
        }

        return best;
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);

        int T = fs.nextInt();

        StringBuilder out = new StringBuilder();

        for (int tc = 1; tc <= T; tc++) {

            int n = fs.nextInt();

            Point[] points = new Point[n];

            for (int i = 0; i < n; i++) {
                int x = fs.nextInt();
                int y = fs.nextInt();

                points[i] = new Point(x, y);
            }

            double r2 = solve(points);

            long answer = -1;

            if (r2 >= 0) {
                answer = (long) Math.floor(3.14 * r2 + 1e-10);
            }

            out.append("Case ")
               .append(tc)
               .append(": ")
               .append(answer)
               .append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {

        BufferedReader br;
        StringTokenizer st;

        FastScanner(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
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
    }
}
