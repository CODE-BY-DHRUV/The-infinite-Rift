import java.io.*;
import java.util.*;

public class Main {

    static final double EPS = 1e-9;

    static class Point {
        double x, y;

        Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    }

    static double cross(Point a, Point b) {
        return a.x * b.y - a.y * b.x;
    }

    static Point subtract(Point a, Point b) {
        return new Point(a.x - b.x, a.y - b.y);
    }

    // Check whether point P is inside the left side of directed edge A -> B
    static boolean inside(Point p, Point a, Point b) {
        Point ab = subtract(b, a);
        Point ap = subtract(p, a);

        return cross(ab, ap) >= -EPS;
    }

    // Find intersection of segment S -> E with line A -> B
    static Point intersection(Point s, Point e, Point a, Point b) {

        Point d = subtract(b, a);
        Point se = subtract(e, s);
        Point as = subtract(a, s);

        double denominator = cross(d, se);

        if (Math.abs(denominator) < EPS) {
            return new Point(s.x, s.y);
        }

        double t = cross(d, as) / denominator;

        return new Point(
            s.x + t * se.x,
            s.y + t * se.y
        );
    }

    // Clip subject polygon using one convex clipping polygon
    static ArrayList<Point> clip(
        ArrayList<Point> subject,
        ArrayList<Point> clipping
    ) {

        ArrayList<Point> current = subject;

        for (int i = 0; i < clipping.size(); i++) {

            if (current.isEmpty()) {
                break;
            }

            Point a = clipping.get(i);
            Point b = clipping.get((i + 1) % clipping.size());

            ArrayList<Point> next = new ArrayList<>();

            Point prev = current.get(current.size() - 1);
            boolean prevInside = inside(prev, a, b);

            for (Point curr : current) {

                boolean currInside = inside(curr, a, b);

                if (currInside) {

                    if (!prevInside) {
                        next.add(intersection(prev, curr, a, b));
                    }

                    next.add(curr);

                } else if (prevInside) {

                    next.add(intersection(prev, curr, a, b));
                }

                prev = curr;
                prevInside = currInside;
            }

            current = next;
        }

        return current;
    }

    // Shoelace formula
    static double area(ArrayList<Point> polygon) {

        int n = polygon.size();

        if (n < 3) {
            return 0.0;
        }

        double sum = 0.0;

        for (int i = 0; i < n; i++) {

            Point a = polygon.get(i);
            Point b = polygon.get((i + 1) % n);

            sum += a.x * b.y - a.y * b.x;
        }

        return Math.abs(sum) / 2.0;
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner(System.in);

        int n = fs.nextInt();

        ArrayList<Point> result = new ArrayList<>();

        // Read first polygon
        int c = fs.nextInt();

        for (int i = 0; i < c; i++) {
            double x = fs.nextInt();
            double y = fs.nextInt();

            result.add(new Point(x, y));
        }

        // Intersect with remaining polygons
        for (int i = 1; i < n; i++) {

            int vertices = fs.nextInt();

            ArrayList<Point> polygon = new ArrayList<>();

            for (int j = 0; j < vertices; j++) {

                double x = fs.nextInt();
                double y = fs.nextInt();

                polygon.add(new Point(x, y));
            }

            result = clip(result, polygon);
        }

        System.out.printf(Locale.US, "%.10f%n", area(result));
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
