import java.io.*;
import java.util.*;

public class Main {

    static final int INF = 1_000_000_000;

    static int n;

    static int[] q;       // transformed permutation
    static int[] comp;

    // Extremal neighbors
    static int[] aMin, aMax;
    static int[] bMin, bMax;

    static IntervalGraph GA;
    static IntervalGraph GB;

    /*
     * Proper interval graph.
     *
     * vertices[] contains the original vertex numbers represented
     * by the interval graph, in increasing order of their left
     * endpoints.
     *
     * left[v], right[v] are the interval endpoints.
     */
    static class IntervalGraph {

        int size;
        int[] vertices;
        int[] position;
        int[] reach;
        int[][] up;
        int[] component;

        IntervalGraph(
                ArrayList<Integer> list,
                int[] left,
                int[] right,
                int n) {

            size = list.size();

            vertices = new int[size];
            position = new int[n + 1];

            Arrays.fill(position, -1);

            for (int i = 0; i < size; i++) {
                vertices[i] = list.get(i);
                position[vertices[i]] = i;
            }

            reach = new int[size];

            /*
             * Because this is a proper interval graph, left endpoints
             * and right endpoints are both non-decreasing.
             *
             * reach[i] = furthest interval intersecting interval i.
             */
            int r = 0;

            for (int i = 0; i < size; i++) {

                if (r < i) {
                    r = i;
                }

                int rightEnd = right[vertices[i]];

                while (r + 1 < size &&
                        left[vertices[r + 1]] <= rightEnd) {
                    r++;
                }

                reach[i] = r;
            }

            /*
             * Components.
             *
             * If reach[i] < i+1, there is a component boundary.
             */
            component = new int[size];

            int cid = 0;

            for (int i = 0; i < size; i++) {

                if (i == 0 || reach[i - 1] < i) {
                    cid++;
                }

                component[i] = cid;
            }

            /*
             * Binary lifting on reach[].
             */
            int LOG = 1;

            while ((1 << LOG) <= size) {
                LOG++;
            }

            up = new int[LOG][size];

            for (int i = 0; i < size; i++) {
                up[0][i] = reach[i];
            }

            for (int k = 1; k < LOG; k++) {
                for (int i = 0; i < size; i++) {
                    up[k][i] = up[k - 1][up[k - 1][i]];
                }
            }
        }

        /*
         * Distance between two intervals.
         */
        int distance(int u, int v) {

            if (u < 0 || v < 0) {
                return INF;
            }

            if (u >= position.length || v >= position.length) {
                return INF;
            }

            int i = position[u];
            int j = position[v];

            if (i < 0 || j < 0) {
                return INF;
            }

            if (i == j) {
                return 0;
            }

            if (i > j) {
                int tmp = i;
                i = j;
                j = tmp;
            }

            if (component[i] != component[j]) {
                return INF;
            }

            /*
             * Find the minimum number of reach jumps needed
             * to reach j.
             */
            int cur = i;
            int ans = 0;

            for (int k = up.length - 1; k >= 0; k--) {

                int next = up[k][cur];

                if (next < j) {
                    cur = next;
                    ans += (1 << k);
                }
            }

            return ans + 1;
        }
    }

    /*
     * Original graph adjacency.
     *
     * After q[i] = n+1-p[i]:
     *
     * edge(i,j), i<j <=> q[i] > q[j]
     */
    static boolean adjacent(int u, int v) {

        if (u == v) {
            return false;
        }

        if (u < v) {
            return q[u] > q[v];
        } else {
            return q[v] > q[u];
        }
    }

    /*
     * Find the A/B sets and all four extremal-neighbor arrays.
     */
    static void buildStructure() {

        ArrayList<Integer> A = new ArrayList<>();
        ArrayList<Integer> B = new ArrayList<>();

        // A = prefix maxima
        int maximum = 0;

        for (int i = 1; i <= n; i++) {

            if (q[i] >= maximum) {
                A.add(i);
                maximum = q[i];
            }
        }

        // B = suffix minima
        int minimum = n + 1;

        for (int i = n; i >= 1; i--) {

            if (q[i] <= minimum) {
                B.add(i);
                minimum = q[i];
            }
        }

        Collections.sort(B);

        aMin = new int[n + 1];
        aMax = new int[n + 1];

        bMin = new int[n + 1];
        bMax = new int[n + 1];

        Arrays.fill(aMin, -1);
        Arrays.fill(aMax, -1);
        Arrays.fill(bMin, -1);
        Arrays.fill(bMax, -1);

        /*
         * q-values of A and B are increasing when their vertices
         * are ordered by vertex number.
         */
        int[] aValues = new int[A.size()];
        int[] bValues = new int[B.size()];

        for (int i = 0; i < A.size(); i++) {
            aValues[i] = q[A.get(i)];
        }

        for (int i = 0; i < B.size(); i++) {
            bValues[i] = q[B.get(i)];
        }

        /*
         * For every v:
         *
         * A-neighbors are A vertices before v with q > q[v].
         *
         * B-neighbors are B vertices after v with q < q[v].
         */
        for (int v = 1; v <= n; v++) {

            // ---------- A neighbors ----------

            int beforeA = lowerBound(A, v);

            if (beforeA > 0) {

                int firstGreater =
                        upperBound(aValues, q[v], 0, beforeA);

                if (firstGreater < beforeA) {
                    aMin[v] = A.get(firstGreater);
                    aMax[v] = A.get(beforeA - 1);
                }
            }

            // ---------- B neighbors ----------

            int afterB = upperBound(A /* dummy */, -1);

            // First B vertex strictly after v
            int firstB = upperBound(B, v);

            // Number of B vertices with q < q[v]
            int countSmaller =
                    lowerBound(bValues, q[v]);

            if (firstB < countSmaller) {
                bMin[v] = B.get(firstB);
                bMax[v] = B.get(countSmaller - 1);
            }
        }

        /*
         * Construct GA.
         *
         * A vertex v becomes an interval:
         *
         * [bMin[v], bMax[v]]
         */
        ArrayList<Integer> listA = new ArrayList<>();

        for (int v : A) {
            if (bMin[v] != -1) {
                listA.add(v);
            }
        }

        /*
         * Construct GB.
         *
         * B vertex v becomes:
         *
         * [aMin[v], aMax[v]]
         */
        ArrayList<Integer> listB = new ArrayList<>();

        for (int v : B) {
            if (aMin[v] != -1) {
                listB.add(v);
            }
        }

        GA = new IntervalGraph(listA, bMin, bMax, n);
        GB = new IntervalGraph(listB, aMin, aMax, n);

        /*
         * Connected components of the original permutation graph.
         *
         * There is no edge crossing a cut k iff:
         *
         * max(q[1..k]) < min(q[k+1..n])
         */
        comp = new int[n + 1];

        int[] prefixMax = new int[n + 1];
        int[] suffixMin = new int[n + 2];

        prefixMax[0] = 0;

        for (int i = 1; i <= n; i++) {
            prefixMax[i] =
                    Math.max(prefixMax[i - 1], q[i]);
        }

        suffixMin[n + 1] = n + 1;

        for (int i = n; i >= 1; i--) {
            suffixMin[i] =
                    Math.min(suffixMin[i + 1], q[i]);
        }

        int cid = 0;

        for (int i = 1; i <= n; i++) {

            if (i == 1 ||
                    prefixMax[i - 1] < suffixMin[i]) {
                cid++;
            }

            comp[i] = cid;
        }
    }

    /*
     * Shortest distance in the original graph.
     */
    static int distance(int u, int v) {

        if (u == v) {
            return 0;
        }

        // Different connected components.
        if (comp[u] != comp[v]) {
            return -1;
        }

        /*
         * Always make u < v.
         */
        if (u > v) {
            int tmp = u;
            u = v;
            v = tmp;
        }

        // Distance 1.
        if (adjacent(u, v)) {
            return 1;
        }

        /*
         * Distance 2:
         *
         * a+(u) -> v
         * or
         * b+(u) -> v
         */
        if (aMax[u] != -1 &&
                adjacent(aMax[u], v)) {
            return 2;
        }

        if (bMax[u] != -1 &&
                adjacent(bMax[u], v)) {
            return 2;
        }

        /*
         * Distance 3:
         *
         * a+(u) -> b-(v)
         * or
         * b+(u) -> a-(v)
         */
        if (aMax[u] != -1 &&
                bMin[v] != -1 &&
                adjacent(aMax[u], bMin[v])) {
            return 3;
        }

        if (bMax[u] != -1 &&
                aMin[v] != -1 &&
                adjacent(bMax[u], aMin[v])) {
            return 3;
        }

        int answer = INF;

        /*
         * Case 1:
         *
         * 2 + 2 * dist_GB(b+(u), b-(v))
         */
        if (bMax[u] != -1 &&
                bMin[v] != -1) {

            int d = GB.distance(
                    bMax[u],
                    bMin[v]
            );

            if (d < INF) {
                answer = Math.min(
                        answer,
                        2 + 2 * d
                );
            }
        }

        /*
         * Case 2:
         *
         * 3 + 2 * dist_GB(
         *          b+(a+(u)),
         *          b-(v)
         *      )
         */
        if (aMax[u] != -1 &&
                bMin[v] != -1) {

            int x = bMax[aMax[u]];

            if (x != -1) {

                int d = GB.distance(x, bMin[v]);

                if (d < INF) {
                    answer = Math.min(
                            answer,
                            3 + 2 * d
                    );
                }
            }
        }

        /*
         * Case 3:
         *
         * 2 + 2 * dist_GA(a+(u), a-(v))
         */
        if (aMax[u] != -1 &&
                aMin[v] != -1) {

            int d = GA.distance(
                    aMax[u],
                    aMin[v]
            );

            if (d < INF) {
                answer = Math.min(
                        answer,
                        2 + 2 * d
                );
            }
        }

        /*
         * Case 4:
         *
         * 3 + 2 * dist_GA(
         *          a+(b+(u)),
         *          a-(v)
         *      )
         */
        if (bMax[u] != -1 &&
                aMin[v] != -1) {

            int x = aMax[bMax[u]];

            if (x != -1) {

                int d = GA.distance(
                        x,
                        aMin[v]
                );

                if (d < INF) {
                    answer = Math.min(
                            answer,
                            3 + 2 * d
                    );
                }
            }
        }

        return answer == INF ? -1 : answer;
    }

    // ------------------------------------------------------------
    // Binary search helpers
    // ------------------------------------------------------------

    // Number of elements < value.
    static int lowerBound(
            ArrayList<Integer> list,
            int value) {

        int lo = 0;
        int hi = list.size();

        while (lo < hi) {

            int mid = (lo + hi) >>> 1;

            if (list.get(mid) < value) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        return lo;
    }

    // Number of elements <= value.
    static int upperBound(
            ArrayList<Integer> list,
            int value) {

        int lo = 0;
        int hi = list.size();

        while (lo < hi) {

            int mid = (lo + hi) >>> 1;

            if (list.get(mid) <= value) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        return lo;
    }

    // First position with array[pos] > value.
    static int upperBound(
            int[] arr,
            int value,
            int from,
            int to) {

        int lo = from;
        int hi = to;

        while (lo < hi) {

            int mid = (lo + hi) >>> 1;

            if (arr[mid] <= value) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        return lo;
    }

    // First position with array[pos] >= value.
    static int lowerBound(
            int[] arr,
            int value) {

        int lo = 0;
        int hi = arr.length;

        while (lo < hi) {

            int mid = (lo + hi) >>> 1;

            if (arr[mid] < value) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        return lo;
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);

        int T = fs.nextInt();

        StringBuilder out = new StringBuilder();

        while (T-- > 0) {

            n = fs.nextInt();
            int qCount = fs.nextInt();

            q = new int[n + 1];

            /*
             * Store transformed permutation:
             *
             * q[i] = n + 1 - p[i]
             */
            for (int i = 1; i <= n; i++) {
                int p = fs.nextInt();
                q[i] = n + 1 - p;
            }

            buildStructure();

            while (qCount-- > 0) {

                int u = fs.nextInt();
                int v = fs.nextInt();

                out.append(distance(u, v))
                   .append('\n');
            }
        }

        System.out.print(out);
    }

    // ------------------------------------------------------------
    // Fast input
    // ------------------------------------------------------------

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

            int result = 0;

            while (c > ' ') {

                result = result * 10 + (c - '0');

                c = read();
            }

            return result * sign;
        }
    }
}
