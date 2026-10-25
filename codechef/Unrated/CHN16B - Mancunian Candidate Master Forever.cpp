
import java.io.*;
import java.util.*;

public class Main {

    static class Point implements Comparable<Point> {
        long s, w, c;

        Point(long s, long w, long c) {
            this.s = s;
            this.w = w;
            this.c = c;
        }

        @Override
        public int compareTo(Point other) {
            if (s != other.s)
                return Long.compare(s, other.s);
            return Long.compare(w, other.w);
        }
    }

    static long cross(Point a, Point b, Point c) {
        return (b.s - a.s) * (c.w - a.w)
             - (b.w - a.w) * (c.s - a.s);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int N = Integer.parseInt(br.readLine().trim());
        Point[] points = new Point[N];

        for (int i = 0; i < N; i++) {
            StringTokenizer st =
                new StringTokenizer(br.readLine());

            long s = Long.parseLong(st.nextToken());
            long w = Long.parseLong(st.nextToken());
            long c = Long.parseLong(st.nextToken());

            points[i] = new Point(s, w, c);
        }

        Arrays.sort(points);

        if (N <= 2) {
            long ans = 0;
            for (Point p : points)
                ans += p.c;
            System.out.println(ans);
            return;
        }

        ArrayList<Point> lower = new ArrayList<>();
        ArrayList<Point> upper = new ArrayList<>();

        // Construct lower hull
        for (Point p : points) {
            while (lower.size() >= 2 &&
                   cross(lower.get(lower.size() - 2),
                         lower.get(lower.size() - 1), p) <= 0) {
                lower.remove(lower.size() - 1);
            }
            lower.add(p);
        }

        // Construct upper hull
        for (int i = N - 1; i >= 0; i--) {
            Point p = points[i];

            while (upper.size() >= 2 &&
                   cross(upper.get(upper.size() - 2),
                         upper.get(upper.size() - 1), p) <= 0) {
                upper.remove(upper.size() - 1);
            }
            upper.add(p);
        }

        // Remove duplicated endpoints
        lower.remove(lower.size() - 1);
        upper.remove(upper.size() - 1);

        lower.addAll(upper);

        long ans = 0;

        for (Point p : lower) {
            ans += p.c;
        }

        System.out.println(ans);
    }
}