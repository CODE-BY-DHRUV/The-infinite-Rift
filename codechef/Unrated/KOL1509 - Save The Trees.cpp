

import java.io.*;
import java.util.*;

public class Main {

    static class Point implements Comparable<Point> {
        long x, y;

        Point(long x, long y) {
            this.x = x;
            this.y = y;
        }

        public int compareTo(Point p) {
            if (x != p.x)
                return Long.compare(x, p.x);

            return Long.compare(y, p.y);
        }
    }

    static long cross(Point a, Point b, Point c) {
        return (b.x - a.x) * (c.y - a.y)
             - (b.y - a.y) * (c.x - a.x);
    }

    static long solve(int[] a, int n) {

        // Generate at most 2*N candidate points
        Point[] points = new Point[2 * (n - 1)];
        int count = 0;

        int min = a[n - 1];
        int max = a[n - 1];

        for (int i = n - 2; i >= 0; i--) {

            points[count++] = new Point(a[i], min);
            points[count++] = new Point(a[i], max);

            min = Math.min(min, a[i]);
            max = Math.max(max, a[i]);
        }

        // Sort candidate points
        Arrays.sort(points, 0, count);

        // Remove duplicate points
        int m = 0;

        for (int i = 0; i < count; i++) {
            if (m == 0 ||
                points[i].x != points[m - 1].x ||
                points[i].y != points[m - 1].y) {

                points[m++] = points[i];
            }
        }

        if (m <= 2)
            return 0;

        Point[] hull = new Point[2 * m];
        int k = 0;

        // Build lower hull
        for (int i = 0; i < m; i++) {

            while (k >= 2 &&
                   cross(hull[k - 2], hull[k - 1],
                         points[i]) <= 0) {
                k--;
            }

            hull[k++] = points[i];
        }

        // Build upper hull
        int lowerSize = k;

        for (int i = m - 2; i >= 0; i--) {

            while (k > lowerSize &&
                   cross(hull[k - 2], hull[k - 1],
                         points[i]) <= 0) {
                k--;
            }

            hull[k++] = points[i];
        }

        // Remove repeated starting point
        k--;

        // Calculate twice the area using shoelace formula
        long area2 = 0;

        for (int i = 0; i < k; i++) {

            Point p = hull[i];
            Point q = hull[(i + 1) % k];

            area2 += p.x * q.y - p.y * q.x;
        }

        return Math.abs(area2);
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner(System.in);

        int t = fs.nextInt();

        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {

            int n = fs.nextInt();

            int[] a = new int[n];

            for (int i = 0; i < n; i++) {
                a[i] = fs.nextInt();
            }

            sb.append(solve(a, n)).append('\n');
        }

        System.out.print(sb);
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
