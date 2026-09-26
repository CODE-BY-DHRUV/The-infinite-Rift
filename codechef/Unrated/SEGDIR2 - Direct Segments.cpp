import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            boolean neg = false;
            if (c == '-') {
                neg = true;
                c = read();
            }

            long res = 0;
            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return neg ? -res : res;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }

    static class Segment {
        long x1, y1, x2, y2;
        long dx, dy;
        double len;

        Segment(long x1, long y1, long x2, long y2) {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;

            dx = x2 - x1;
            dy = y2 - y1;
            len = Math.hypot(dx, dy);
        }
    }

    /*
     * cross(a,b)
     */
    static long cross(long ax, long ay, long bx, long by) {
        return ax * by - ay * bx;
    }

    /*
     * dot(a,b)
     */
    static long dot(long ax, long ay, long bx, long by) {
        return ax * bx + ay * by;
    }

    /*
     * For a non-parallel pair, suppose P is their intersection.
     *
     * p = signed distance from A to P, measured in the direction A -> B.
     *
     * If direction = +1:
     *      the segment occupies [t, L+t]
     *
     * Hence P is inside for:
     *      max(0,p-L) <= t <= p
     *
     * If direction = -1:
     *      the segment occupies [-t,L-t]
     *
     * Hence:
     *      max(0,-p) <= t <= L-p
     */
    static double[] interval(double p, double L, int dir) {
        double lo, hi;

        if (dir == 1) {
            lo = Math.max(0.0, p - L);
            hi = p;
        } else {
            lo = Math.max(0.0, -p);
            hi = L - p;
        }

        if (hi < lo - 1e-10) {
            return null;
        }

        return new double[]{lo, hi};
    }

    static boolean overlap(double[] a, double[] b) {
        if (a == null || b == null) return false;

        double l = Math.max(a[0], b[0]);
        double r = Math.min(a[1], b[1]);

        double eps = 1e-9 *
                Math.max(1.0, Math.max(Math.abs(l), Math.abs(r)));

        return l <= r + eps;
    }

    /*
     * Check whether two COLLINEAR segments collide for
     * the selected directions.
     *
     * We project everything onto the direction of segment a.
     */
    static boolean collinearCollision(
            Segment a,
            Segment b,
            int da,
            int db
    ) {
        long ax = a.dx;
        long ay = a.dy;

        long lenSq = dot(ax, ay, ax, ay);

        /*
         * Coordinate of b's first endpoint on a's axis,
         * multiplied by |a|^2.
         */
        long q = dot(
                b.x1 - a.x1,
                b.y1 - a.y1,
                ax,
                ay
        );

        /*
         * Projection of b's direction on a's direction.
         */
        long proj = dot(b.dx, b.dy, ax, ay);

        long p1 = q;
        long p2 = q + proj;

        long bLeft = Math.min(p1, p2);
        long bRight = Math.max(p1, p2);

        /*
         * Segment a initially occupies [0,lenSq].
         */
        long aLeft = 0;
        long aRight = lenSq;

        /*
         * Determine whether b's positive direction is the same
         * or opposite to a's positive direction.
         */
        int orient = (proj >= 0 ? 1 : -1);

        /*
         * Movement in our scaled coordinate.
         *
         * da = +1 means A -> B
         * da = -1 means B -> A
         *
         * Since actual velocity is unit length, after multiplying
         * the coordinate by |a|, velocity becomes ±|a|.
         *
         * We can use the fact that both segments move at unit speed.
         * For the collision existence test, the relative direction
         * is what matters.
         */
        int va = da;
        int vb = db * orient;

        /*
         * Same velocity:
         *
         * The relative position never changes.
         * Therefore collision happens iff they already overlap.
         */
        if (va == vb) {
            return Math.max(aLeft, bLeft) <=
                    Math.min(aRight, bRight);
        }

        /*
         * Different velocities:
         *
         * Their relative speed is 2.
         *
         * They collide iff the two intervals approach each other.
         *
         * We can determine which interval is initially left.
         */
        if (aRight < bLeft) {
            /*
             * a is completely left of b.
             *
             * a moves right iff va=+1
             * b moves left iff vb=-1
             */
            return va == 1 && vb == -1;
        }

        if (bRight < aLeft) {
            /*
             * b is completely left of a.
             *
             * b moves right iff vb=+1
             * a moves left iff va=-1
             */
            return vb == 1 && va == -1;
        }

        /*
         * Already overlapping at t=0.
         */
        return true;
    }

    /*
     * bad[x][y] tells whether:
     *
     * x = 0 -> segment i moves A -> B
     * x = 1 -> segment i moves B -> A
     *
     * y similarly for segment j.
     */
    static boolean[][] getBad(Segment a, Segment b) {

        boolean[][] bad = new boolean[2][2];

        long cr = cross(a.dx, a.dy, b.dx, b.dy);

        /*
         * Parallel / collinear.
         */
        if (cr == 0) {

            long qx = b.x1 - a.x1;
            long qy = b.y1 - a.y1;

            /*
             * Parallel but on different lines.
             */
            if (cross(a.dx, a.dy, qx, qy) != 0) {
                return bad;
            }

            /*
             * Collinear.
             */
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {

                    int da = (i == 0 ? 1 : -1);
                    int db = (j == 0 ? 1 : -1);

                    bad[i][j] =
                            collinearCollision(a, b, da, db);
                }
            }

            return bad;
        }

        /*
         * Non-parallel lines have exactly one intersection point.
         *
         * Parameter on line a:
         *
         * lambda =
         * cross(B-A, b.direction) /
         * cross(a.direction,b.direction)
         *
         * Distance from a's starting point:
         * pA = lambda * |a|
         */
        long qx = b.x1 - a.x1;
        long qy = b.y1 - a.y1;

        double lambdaA =
                (double) cross(qx, qy, b.dx, b.dy) /
                (double) cr;

        double pA = lambdaA * a.len;

        /*
         * Parameter on line b.
         */
        long rx = a.x1 - b.x1;
        long ry = a.y1 - b.y1;

        double lambdaB =
                (double) cross(rx, ry, a.dx, a.dy) /
                (double) (-cr);

        double pB = lambdaB * b.len;

        double[][] ia = new double[2][];
        double[][] ib = new double[2][];

        ia[0] = interval(pA, a.len, 1);
        ia[1] = interval(pA, a.len, -1);

        ib[0] = interval(pB, b.len, 1);
        ib[1] = interval(pB, b.len, -1);

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                bad[i][j] = overlap(ia[i], ib[j]);
            }
        }

        return bad;
    }

    // ------------------------------------------------------------
    // 2-SAT
    // ------------------------------------------------------------

    static void addEdge(
            int u,
            int v,
            int[] head,
            int[] to,
            int[] next,
            int[] ec
    ) {
        int e = ec[0]++;

        to[e] = v;
        next[e] = head[u];
        head[u] = e;
    }

    /*
     * Node:
     *
     * 2*i     -> i chooses A -> B
     * 2*i + 1 -> i chooses B -> A
     *
     * opposite node = node ^ 1
     */
    static int opposite(int x) {
        return x ^ 1;
    }

    /*
     * Forbid:
     *
     * i = di AND j = dj
     *
     * Therefore:
     *
     * (i != di) OR (j != dj)
     *
     * which becomes two implications.
     */
    static void forbid(
            int i,
            int di,
            int j,
            int dj,
            int[] head,
            int[] to,
            int[] next,
            int[] ec
    ) {

        int ni = 2 * i + (di == -1 ? 1 : 0);
        int nj = 2 * j + (dj == -1 ? 1 : 0);

        addEdge(
                ni,
                opposite(nj),
                head, to, next, ec
        );

        addEdge(
                nj,
                opposite(ni),
                head, to, next, ec
        );
    }

    static int timer;
    static int sccCount;
    static int[] disc;
    static int[] low;
    static int[] comp;
    static boolean[] onStack;
    static int[] stack;
    static int stackSize;

    static void dfs(
            int u,
            int[] head,
            int[] to,
            int[] next
    ) {

        disc[u] = low[u] = ++timer;

        stack[stackSize++] = u;
        onStack[u] = true;

        for (int e = head[u]; e != -1; e = next[e]) {

            int v = to[e];

            if (disc[v] == 0) {

                dfs(v, head, to, next);

                low[u] =
                        Math.min(low[u], low[v]);

            } else if (onStack[v]) {

                low[u] =
                        Math.min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {

            while (true) {

                int v = stack[--stackSize];

                onStack[v] = false;
                comp[v] = sccCount;

                if (v == u) break;
            }

            sccCount++;
        }
    }

    static boolean solve(Segment[] s) {

        int n = s.length;
        int nodes = 2 * n;

        /*
         * At most four forbidden direction combinations
         * per pair, and every forbidden combination creates
         * two implications.
         *
         * So 4 * C(n,2) implication edges are enough.
         */
        int maxEdges =
                4 * n * (n - 1) / 2;

        int[] head = new int[nodes];
        Arrays.fill(head, -1);

        int[] to = new int[maxEdges];
        int[] next = new int[maxEdges];
        int[] ec = new int[1];

        /*
         * Construct the implication graph.
         */
        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {

                boolean[][] bad =
                        getBad(s[i], s[j]);

                int badCount = 0;

                for (int x = 0; x < 2; x++) {
                    for (int y = 0; y < 2; y++) {

                        if (bad[x][y]) {
                            badCount++;
                        }
                    }
                }

                /*
                 * Every one of the four assignments is bad.
                 */
                if (badCount == 4) {
                    return false;
                }

                for (int x = 0; x < 2; x++) {

                    for (int y = 0; y < 2; y++) {

                        if (!bad[x][y]) continue;

                        int di =
                                (x == 0 ? 1 : -1);

                        int dj =
                                (y == 0 ? 1 : -1);

                        forbid(
                                i, di,
                                j, dj,
                                head, to, next, ec
                        );
                    }
                }
            }
        }

        /*
         * SCC.
         */
        timer = 0;
        sccCount = 0;
        stackSize = 0;

        disc = new int[nodes];
        low = new int[nodes];
        comp = new int[nodes];
        onStack = new boolean[nodes];
        stack = new int[nodes];

        for (int i = 0; i < nodes; i++) {
            if (disc[i] == 0) {
                dfs(i, head, to, next);
            }
        }

        /*
         * x and !x in the same SCC => impossible.
         */
        for (int i = 0; i < n; i++) {

            if (comp[2 * i] ==
                comp[2 * i + 1]) {

                return false;
            }
        }

        return true;
    }

    public static void main(String[] args)
            throws Exception {

        FastScanner fs = new FastScanner();

        StringBuilder ans =
                new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();

            Segment[] s =
                    new Segment[n];

            for (int i = 0; i < n; i++) {

                long x = fs.nextLong();
                long y = fs.nextLong();

                long X = fs.nextLong();
                long Y = fs.nextLong();

                s[i] =
                        new Segment(x, y, X, Y);
            }

            ans.append(
                    solve(s) ? "YES\n" : "NO\n"
            );
        }

        System.out.print(ans);
    }
}