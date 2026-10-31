
import java.util.*;

public class Main {

    static class Point {
        double x, y;

        Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    }

    static Point[] p;
    static int n;
    static int required;

    static double bestX, bestY;

    static boolean check(double r) {
        double r2 = r * r;
        double eps = 1e-10 * Math.max(1.0, r2);

        // Check centers at employee positions
        for (int i = 0; i < n; i++) {
            if (count(p[i].x, p[i].y, r2, eps)) {
                bestX = p[i].x;
                bestY = p[i].y;
                return true;
            }
        }

        // Check intersections of circles for every pair
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                double dx = p[j].x - p[i].x;
                double dy = p[j].y - p[i].y;

                double d2 = dx * dx + dy * dy;

                if (d2 > 4 * r2 + eps) {
                    continue;
                }

                double d = Math.sqrt(d2);

                double mx = (p[i].x + p[j].x) / 2.0;
                double my = (p[i].y + p[j].y) / 2.0;

                double h2 = r2 - d2 / 4.0;
                double h = Math.sqrt(Math.max(0, h2));

                double ux = -dy / d;
                double uy = dx / d;

                // First intersection
                double cx = mx + h * ux;
                double cy = my + h * uy;

                if (count(cx, cy, r2, eps)) {
                    bestX = cx;
                    bestY = cy;
                    return true;
                }

                // Second intersection
                cx = mx - h * ux;
                cy = my - h * uy;

                if (count(cx, cy, r2, eps)) {
                    bestX = cx;
                    bestY = cy;
                    return true;
                }
            }
        }

        return false;
    }

    static boolean count(double cx, double cy,
                         double r2, double eps) {

        int covered = 0;

        for (int i = 0; i < n; i++) {
            double dx = p[i].x - cx;
            double dy = p[i].y - cy;

            double dist2 = dx * dx + dy * dy;

            if (dist2 <= r2 + eps) {
                covered++;
            }

            if (covered >= required) {
                return true;
            }
        }

        return false;
    }

    static void solve(Scanner sc) {

        n = sc.nextInt();
        p = new Point[n];

        for (int i = 0; i < n; i++) {
            double x = sc.nextDouble();
            double y = sc.nextDouble();

            p[i] = new Point(x, y);
        }

        required = n - 4;

        // Find an upper bound for the radius
        double low = 0;
        double high = 0;

        for (int i = 1; i < n; i++) {
            double dx = p[i].x - p[0].x;
            double dy = p[i].y - p[0].y;

            high = Math.max(high,
                    Math.sqrt(dx * dx + dy * dy));
        }

        // Binary search
        for (int iter = 0; iter < 70; iter++) {

            double mid = (low + high) / 2.0;

            if (check(mid)) {
                high = mid;
            } else {
                low = mid;
            }
        }

        // Get the final valid center
        check(high);

        System.out.printf(Locale.US,
                "%.10f %.10f %.10f%n",
                bestX, bestY, high);
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            solve(sc);
        }

        sc.close();
    }
}
