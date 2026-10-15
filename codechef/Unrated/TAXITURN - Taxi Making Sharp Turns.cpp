import java.io.*;
import java.util.*;

public class Main {

    static class Point {
        int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static boolean sharp(Point a, Point b, Point c) {
        long ux = b.x - a.x;
        long uy = b.y - a.y;
        long vx = c.x - b.x;
        long vy = c.y - b.y;

        long dot = ux * vx + uy * vy;
        long cross = ux * vy - uy * vx;

        // The turn angle is greater than 45 degrees.
        return dot < 0 || cross * cross > dot * dot;
    }

    static boolean valid(Point[] p) {
        for (int i = 1; i < p.length - 1; i++) {
            if (sharp(p[i - 1], p[i], p[i + 1])) {
                return false;
            }
        }
        return true;
    }

    static boolean canFix(Point[] p) {
        int n = p.length;

        for (int i = 0; i < n; i++) {
            Point old = p[i];

            for (int x = 0; x <= 50; x++) {
                for (int y = 0; y <= 50; y++) {
                    if (x == old.x && y == old.y) {
                        continue;
                    }

                    boolean duplicate = false;
                    for (int j = 0; j < n; j++) {
                        if (j != i && p[j].x == x && p[j].y == y) {
                            duplicate = true;
                            break;
                        }
                    }

                    if (duplicate) {
                        continue;
                    }

                    p[i] = new Point(x, y);

                    if (valid(p)) {
                        p[i] = old;
                        return true;
                    }
                }
            }

            p[i] = old;
        }

        return false;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());
            Point[] p = new Point[n];

            for (int i = 0; i < n; i++) {
                StringTokenizer st =
                    new StringTokenizer(br.readLine());
                p[i] = new Point(
                    Integer.parseInt(st.nextToken()),
                    Integer.parseInt(st.nextToken())
                );
            }

            boolean alreadyValid = valid(p);
            boolean fixable = alreadyValid || canFix(p);

            out.append(alreadyValid ? "yes" : "no")
               .append(' ')
               .append(fixable ? "yes" : "no")
               .append('\n');
        }

        System.out.print(out);
    }
}