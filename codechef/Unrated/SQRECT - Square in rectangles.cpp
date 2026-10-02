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

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            int res = 0;
            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }
            return res * sign;
        }
    }

    /*
     * Segment tree maintains:
     *
     * H = A - B
     * J = C - D
     * F = min(A,B) + min(C,D)
     *
     * Each of H/J/F supports range addition.
     */
    static class SegTree {
        int n;

        int[] maxH;
        int[] maxJ;
        int[] maxF;

        int[] lazyH;
        int[] lazyJ;
        int[] lazyF;

        SegTree(int[] H, int[] J) {
            n = H.length;

            int sz = 4 * n + 5;

            maxH = new int[sz];
            maxJ = new int[sz];
            maxF = new int[sz];

            lazyH = new int[sz];
            lazyJ = new int[sz];
            lazyF = new int[sz];

            build(1, 0, n - 1, H, J);
        }

        void build(int v, int l, int r, int[] H, int[] J) {
            if (l == r) {
                maxH[v] = H[l];
                maxJ[v] = J[l];
                maxF[v] = 0;
                return;
            }

            int mid = (l + r) >>> 1;

            build(v << 1, l, mid, H, J);
            build(v << 1 | 1, mid + 1, r, H, J);

            pull(v);
        }

        void pull(int v) {
            maxH[v] = Math.max(maxH[v << 1], maxH[v << 1 | 1]);
            maxJ[v] = Math.max(maxJ[v << 1], maxJ[v << 1 | 1]);
            maxF[v] = Math.max(maxF[v << 1], maxF[v << 1 | 1]);
        }

        void applyH(int v, int delta) {
            maxH[v] += delta;
            lazyH[v] += delta;
        }

        void applyJ(int v, int delta) {
            maxJ[v] += delta;
            lazyJ[v] += delta;
        }

        void applyF(int v, int delta) {
            maxF[v] += delta;
            lazyF[v] += delta;
        }

        void applyHF(int v, int dh, int df) {
            applyH(v, dh);
            applyF(v, df);
        }

        void applyJF(int v, int dj, int df) {
            applyJ(v, dj);
            applyF(v, df);
        }

        void push(int v) {
            if (lazyH[v] != 0) {
                applyH(v << 1, lazyH[v]);
                applyH(v << 1 | 1, lazyH[v]);
                lazyH[v] = 0;
            }

            if (lazyJ[v] != 0) {
                applyJ(v << 1, lazyJ[v]);
                applyJ(v << 1 | 1, lazyJ[v]);
                lazyJ[v] = 0;
            }

            if (lazyF[v] != 0) {
                applyF(v << 1, lazyF[v]);
                applyF(v << 1 | 1, lazyF[v]);
                lazyF[v] = 0;
            }
        }

        /*
         * H is updated on [hL, hR].
         * F is updated on [fL, fR].
         *
         * The F interval is always a subset of the H interval.
         */
        void updateHF(
                int v, int l, int r,
                int hL, int hR,
                int fL, int fR,
                int dh, int df
        ) {
            if (r < hL || hR < l)
                return;

            if (l >= hL && r <= hR) {

                // Entire node is inside F interval.
                if (fL <= fR && l >= fL && r <= fR) {
                    applyHF(v, dh, df);
                    return;
                }

                // Entire node is outside F interval.
                if (fL > fR || r < fL || l > fR) {
                    applyH(v, dh);
                    return;
                }
            }

            if (l == r) {
                applyH(v, dh);

                if (fL <= fR && l >= fL && l <= fR)
                    applyF(v, df);

                return;
            }

            push(v);

            int mid = (l + r) >>> 1;

            updateHF(
                    v << 1, l, mid,
                    hL, hR, fL, fR, dh, df
            );

            updateHF(
                    v << 1 | 1, mid + 1, r,
                    hL, hR, fL, fR, dh, df
            );

            pull(v);
        }

        /*
         * Same thing for J and F.
         */
        void updateJF(
                int v, int l, int r,
                int jL, int jR,
                int fL, int fR,
                int dj, int df
        ) {
            if (r < jL || jR < l)
                return;

            if (l >= jL && r <= jR) {

                if (fL <= fR && l >= fL && r <= fR) {
                    applyJF(v, dj, df);
                    return;
                }

                if (fL > fR || r < fL || l > fR) {
                    applyJ(v, dj);
                    return;
                }
            }

            if (l == r) {
                applyJ(v, dj);

                if (fL <= fR && l >= fL && l <= fR)
                    applyF(v, df);

                return;
            }

            push(v);

            int mid = (l + r) >>> 1;

            updateJF(
                    v << 1, l, mid,
                    jL, jR, fL, fR, dj, df
            );

            updateJF(
                    v << 1 | 1, mid + 1, r,
                    jL, jR, fL, fR, dj, df
            );

            pull(v);
        }

        void updateHF(
                int hL, int hR,
                int fL, int fR,
                int dh, int df
        ) {
            if (hL > hR)
                return;

            updateHF(
                    1, 0, n - 1,
                    hL, hR,
                    fL, fR,
                    dh, df
            );
        }

        void updateJF(
                int jL, int jR,
                int fL, int fR,
                int dj, int df
        ) {
            if (jL > jR)
                return;

            updateJF(
                    1, 0, n - 1,
                    jL, jR,
                    fL, fR,
                    dj, df
            );
        }

        int getH(int pos) {
            return getH(1, 0, n - 1, pos);
        }

        int getH(int v, int l, int r, int pos) {
            if (l == r)
                return maxH[v];

            push(v);

            int mid = (l + r) >>> 1;

            if (pos <= mid)
                return getH(v << 1, l, mid, pos);
            else
                return getH(v << 1 | 1, mid + 1, r, pos);
        }

        int getJ(int pos) {
            return getJ(1, 0, n - 1, pos);
        }

        int getJ(int v, int l, int r, int pos) {
            if (l == r)
                return maxJ[v];

            push(v);

            int mid = (l + r) >>> 1;

            if (pos <= mid)
                return getJ(v << 1, l, mid, pos);
            else
                return getJ(v << 1 | 1, mid + 1, r, pos);
        }

        int maxF() {
            return maxF[1];
        }
    }

    static int lowerBound(int[] a, int x) {
        int l = 0, r = a.length;

        while (l < r) {
            int m = (l + r) >>> 1;

            if (a[m] >= x)
                r = m;
            else
                l = m + 1;
        }

        return l;
    }

    static int upperBound(int[] a, int x) {
        int l = 0, r = a.length;

        while (l < r) {
            int m = (l + r) >>> 1;

            if (a[m] > x)
                r = m;
            else
                l = m + 1;
        }

        return l;
    }

    static int[] unique(int[] a) {
        if (a.length == 0)
            return a;

        int cnt = 1;

        for (int i = 1; i < a.length; i++) {
            if (a[i] != a[cnt - 1])
                a[cnt++] = a[i];
        }

        return Arrays.copyOf(a, cnt);
    }

    /*
     * Check whether a square of side s can be secured by k squads.
     */
    static boolean feasible(
            int[] xs,
            int[] ysOriginal,
            int k,
            int s
    ) {
        int n = xs.length;

        /*
         * Candidate Y positions.
         * An optimal Y can be chosen among:
         *
         * yi
         * yi - s
         */
        int[] tmpY = new int[2 * n];

        for (int i = 0; i < n; i++) {
            tmpY[i] = ysOriginal[i];
            tmpY[n + i] = ysOriginal[i] - s;
        }

        Arrays.sort(tmpY);
        int[] coordY = unique(tmpY);

        int m = coordY.length;

        /*
         * Initial state:
         *
         * X is far to the left.
         * Therefore every point is in R.
         *
         * A = C = 0
         * B = number of R points above Y+s
         * D = number of R points below Y
         *
         * H = A-B = -B
         * J = C-D = -D
         */
        int[] sortedY = ysOriginal.clone();
        Arrays.sort(sortedY);

        int[] H = new int[m];
        int[] J = new int[m];

        for (int i = 0; i < m; i++) {
            int y = coordY[i];

            int first = lowerBound(sortedY, y + s);
            int B = n - first;

            int last = upperBound(sortedY, y);
            int D = last;

            H[i] = -B;
            J[i] = -D;
        }

        SegTree st = new SegTree(H, J);

        /*
         * p = first index where H >= 0
         * q = last index where J >= 0
         */
        int p = m;

        for (int i = 0; i < m; i++) {
            if (H[i] >= 0) {
                p = i;
                break;
            }
        }

        int q = -1;

        for (int i = m - 1; i >= 0; i--) {
            if (J[i] >= 0) {
                q = i;
                break;
            }
        }

        /*
         * For each point we need two X events:
         *
         * x_i     : M -> L
         * x_i - s : R -> M
         *
         * Pack:
         *
         * high 32 bits = shifted X
         * bit 31       = event type
         * low 31 bits  = point id
         *
         * type 0 = M -> L
         * type 1 = R -> M
         */
        long[] events = new long[2 * n];

        final int XSHIFT = 3_000_000;

        for (int i = 0; i < n; i++) {
            long e1 =
                    ((long) (xs[i] + XSHIFT) << 32)
                            | (long) i;

            long e2 =
                    ((long) (xs[i] - s + XSHIFT) << 32)
                            | (1L << 31)
                            | (long) i;

            events[2 * i] = e1;
            events[2 * i + 1] = e2;
        }

        Arrays.sort(events);

        int[] yi = new int[n];
        int[] yMinus = new int[n];

        for (int i = 0; i < n; i++) {
            yi[i] = lowerBound(coordY, ysOriginal[i]);
            yMinus[i] = lowerBound(coordY, ysOriginal[i] - s);
        }

        int pos = 0;

        while (pos < events.length) {

            int xKey = (int) (events[pos] >>> 32);

            int end = pos + 1;

            while (end < events.length &&
                    (int) (events[end] >>> 32) == xKey) {
                end++;
            }

            /*
             * First process M -> L.
             *
             * These points have x == X and therefore ARE in L
             * for the exact X position.
             */
            for (int z = pos; z < end; z++) {
                long e = events[z];

                int type = (int) ((e >>> 31) & 1L);

                if (type != 0)
                    continue;

                int id = (int) (e & 0x7fffffffL);

                int a = yi[id];
                int b = yMinus[id];

                /*
                 * Adding this point to L:
                 *
                 * A increases for Y >= y.
                 *
                 * F increases where A < B, i.e. H < 0.
                 * Those positions are [a, p-1].
                 *
                 * C increases for Y <= y-s.
                 *
                 * F increases where C < D, i.e. J < 0.
                 * Those positions are [q+1, b].
                 */

                st.updateHF(
                        a, m - 1,
                        a, p - 1,
                        +1, +1
                );

                st.updateJF(
                        0, b,
                        q + 1, b,
                        +1, +1
                );

                /*
                 * H and J increased.
                 * Hence p can only move left and q can only move right.
                 */

                if (p == m) {
                    if (st.getH(m - 1) >= 0)
                        p = m - 1;
                }

                while (p > 0 && st.getH(p - 1) >= 0)
                    p--;

                while (q + 1 < m &&
                        st.getJ(q + 1) >= 0)
                    q++;
            }

            /*
             * Now this represents the exact X coordinate.
             */
            if (st.maxF() >= k)
                return true;

            /*
             * Now move just to the right of X.
             *
             * Points with x-s == X leave R:
             *
             * R -> M
             */
            for (int z = pos; z < end; z++) {
                long e = events[z];

                int type = (int) ((e >>> 31) & 1L);

                if (type != 1)
                    continue;

                int id = (int) (e & 0x7fffffffL);

                int a = yi[id];
                int b = yMinus[id];

                /*
                 * B decreases for Y <= y-s.
                 *
                 * F decreases where A >= B, i.e. H >= 0.
                 * Those positions are [p, b].
                 */
                st.updateHF(
                        0, b,
                        p, b,
                        +1, -1
                );

                /*
                 * D decreases for Y >= y.
                 *
                 * F decreases where C >= D, i.e. J >= 0.
                 * Those positions are [a, q].
                 */
                st.updateJF(
                        a, m - 1,
                        a, q,
                        +1, -1
                );

                /*
                 * Again H/J only increase.
                 */
                if (p == m) {
                    if (st.getH(m - 1) >= 0)
                        p = m - 1;
                }

                while (p > 0 && st.getH(p - 1) >= 0)
                    p--;

                while (q + 1 < m &&
                        st.getJ(q + 1) >= 0)
                    q++;
            }

            pos = end;
        }

        return false;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            int n = fs.nextInt();
            int k = fs.nextInt();

            int[] x = new int[n];
            int[] y = new int[n];

            for (int i = 0; i < n; i++) {
                x[i] = fs.nextInt();
                y[i] = fs.nextInt();
            }

            /*
             * Coordinates are within [-1e6, 1e6],
             * so the maximum possible side is <= 2e6.
             */
            int lo = 0;
            int hi = 2_000_000;

            while (lo < hi) {
                int mid = (lo + hi + 1) >>> 1;

                if (feasible(x, y, k, mid))
                    lo = mid;
                else
                    hi = mid - 1;
            }

            out.append(lo).append('\n');
        }

        System.out.print(out);
    }
}
