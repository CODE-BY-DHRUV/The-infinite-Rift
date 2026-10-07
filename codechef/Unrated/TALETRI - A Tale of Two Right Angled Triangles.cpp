
import java.io.*;
import java.util.*;

public class Main {

    // Two intervals of lengths p and q can have
    // total bounding span equal to target iff
    // target >= max(p, q).
    static boolean can(long p, long q, long target) {
        return target >= Math.max(p, q);
    }

    /*
     * Triangle ABC:
     *
     * AC = b
     * BC = a
     * AB = c
     *
     * type 0:
     *
     *      A
     *      |
     *      | b
     *      |
     *      C-------B
     *          a
     *
     * type 1:
     *
     * A-------C
     *     b
     *     |
     *     | a
     *     |
     *     B
     */
    static long[][] makeTriangle1(
            long x, long y,
            long a, long b,
            int type) {

        long[][] p = new long[3][2];

        if (type == 0) {
            // C
            p[2][0] = x;
            p[2][1] = y;

            // A: AC = b
            p[0][0] = x;
            p[0][1] = y + b;

            // B: BC = a
            p[1][0] = x + a;
            p[1][1] = y;

        } else {
            // C
            p[2][0] = x;
            p[2][1] = y;

            // A: AC = b
            p[0][0] = x + b;
            p[0][1] = y;

            // B: BC = a
            p[1][0] = x;
            p[1][1] = y + a;
        }

        return p;
    }

    /*
     * Triangle DEF:
     *
     * DF = e
     * EF = d
     * DE = f
     *
     * type 0:
     *
     *      D
     *      |
     *      | e
     *      |
     *      F-------E
     *          d
     *
     * type 1:
     *
     * D-------F
     *     e
     *     |
     *     | d
     *     |
     *     E
     */
    static long[][] makeTriangle2(
            long x, long y,
            long d, long e,
            int type) {

        long[][] p = new long[3][2];

        if (type == 0) {
            // F
            p[2][0] = x;
            p[2][1] = y;

            // D: DF = e
            p[0][0] = x;
            p[0][1] = y + e;

            // E: EF = d
            p[1][0] = x + d;
            p[1][1] = y;

        } else {
            // F
            p[2][0] = x;
            p[2][1] = y;

            // D: DF = e
            p[0][0] = x + e;
            p[0][1] = y;

            // E: EF = d
            p[1][0] = x;
            p[1][1] = y + d;
        }

        return p;
    }

    /*
     * Try to construct a solution where the
     * minimum enclosing rectangle is W x H.
     */
    static long[][] build(
            long a, long b,
            long d, long e,
            long W, long H,
            int type1, int type2) {

        // Bounding-box dimensions of triangle 1
        long w1 = (type1 == 0) ? a : b;
        long h1 = (type1 == 0) ? b : a;

        // Bounding-box dimensions of triangle 2
        long w2 = (type2 == 0) ? d : e;
        long h2 = (type2 == 0) ? e : d;

        // The target rectangle must be large enough
        // to contain each triangle's bounding box.
        if (!can(w1, w2, W)) {
            return null;
        }

        if (!can(h1, h2, H)) {
            return null;
        }

        /*
         * Put triangle 1 at the left/bottom.
         *
         * Its x-range is [0, w1].
         * Its y-range is [0, h1].
         */
        long x1 = 0;
        long y1 = 0;

        /*
         * Put triangle 2 so that its right/top boundary
         * reaches exactly W/H.
         *
         * x-range = [W-w2, W]
         * y-range = [H-h2, H]
         *
         * Since W >= w2 and H >= h2,
         * these coordinates are non-negative.
         */
        long x2 = W - w2;
        long y2 = H - h2;

        long[][] t1 =
                makeTriangle1(x1, y1, a, b, type1);

        long[][] t2 =
                makeTriangle2(x2, y2, d, e, type2);

        long[][] ans = new long[6][2];

        for (int i = 0; i < 3; i++) {
            ans[i][0] = t1[i][0];
            ans[i][1] = t1[i][1];

            ans[i + 3][0] = t2[i][0];
            ans[i + 3][1] = t2[i][1];
        }

        return ans;
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br =
                new BufferedReader(
                        new InputStreamReader(System.in));

        StringBuilder out = new StringBuilder();

        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {

            StringTokenizer st =
                    new StringTokenizer(br.readLine());

            long a = Long.parseLong(st.nextToken());
            long b = Long.parseLong(st.nextToken());
            long c = Long.parseLong(st.nextToken());

            long d = Long.parseLong(st.nextToken());
            long e = Long.parseLong(st.nextToken());
            long f = Long.parseLong(st.nextToken());

            long L = Long.parseLong(st.nextToken());
            long R = Long.parseLong(st.nextToken());

            long[][] answer = null;

            /*
             * Try:
             *   2 orientations for triangle 1
             *   2 orientations for triangle 2
             *   2 assignments of L and R
             *
             * Total = 8 cases.
             */
            for (int type1 = 0; type1 < 2 && answer == null; type1++) {

                for (int type2 = 0; type2 < 2 && answer == null; type2++) {

                    // Rectangle = L x R
                    answer = build(
                            a, b,
                            d, e,
                            L, R,
                            type1, type2
                    );

                    // Rectangle = R x L
                    if (answer == null) {
                        answer = build(
                                a, b,
                                d, e,
                                R, L,
                                type1, type2
                        );
                    }
                }
            }

            if (answer == null) {
                out.append("-1\n");
            } else {
                for (int i = 0; i < 6; i++) {
                    out.append(answer[i][0])
                       .append(' ')
                       .append(answer[i][1])
                       .append('\n');
                }
            }
        }

        System.out.print(out);
    }
}

