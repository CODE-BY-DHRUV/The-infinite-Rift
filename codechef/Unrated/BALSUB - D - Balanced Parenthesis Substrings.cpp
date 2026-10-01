
import java.io.*;
import java.util.*;

public class Main {

    static final int MAX_M = 100;
    static final int MAX_K = MAX_M * (MAX_M + 1) / 2;

    /*
     * prevPart[m][k] = the last degree d used to construct
     * a partition of m whose extra value is k.
     *
     * If:
     *
     *   k = sum C(d_i, 2)
     *   m = sum d_i
     *
     * then prevPart lets us reconstruct the d_i.
     */
    static int[][] prevPart = new int[MAX_M + 1][MAX_K + 1];

    static void precompute() {

        /*
         * reachable[m][k]:
         *
         * Can we write m as a sum of positive integers d_i
         * such that
         *
         *   sum C(d_i, 2) = k ?
         */
        boolean[][] reachable =
                new boolean[MAX_M + 1][MAX_K + 1];

        reachable[0][0] = true;

        /*
         * We build partitions in nondecreasing order.
         *
         * last[d] is not needed because we can instead use
         * the standard unbounded-knapsack ordering:
         *
         * iterate d from 1 to 100,
         * then m from d to MAX_M.
         */
        for (int d = 1; d <= MAX_M; d++) {

            int add = d * (d - 1) / 2;

            for (int m = d; m <= MAX_M; m++) {

                for (int k = add; k <= MAX_K; k++) {

                    if (!reachable[m - d][k - add]) {
                        continue;
                    }

                    if (!reachable[m][k]) {

                        reachable[m][k] = true;
                        prevPart[m][k] = d;
                    }
                }
            }
        }
    }

    /*
     * Construct a balanced parenthesis string from a partition
     *
     * d1 + d2 + ... + dq = m
     *
     * where
     *
     * sum C(di,2) = extra.
     */
    static String construct(int m, int extra) {

        ArrayList<Integer> parts = new ArrayList<>();

        int curM = m;
        int curK = extra;

        while (curM > 0) {

            int d = prevPart[curM][curK];

            if (d == 0) {
                return null;
            }

            parts.add(d);

            curM -= d;
            curK -= d * (d - 1) / 2;
        }

        /*
         * parts contains the degrees of the real nodes plus
         * the imaginary root.
         *
         * We use the largest degree for the imaginary root.
         */
        int rootIndex = 0;

        for (int i = 1; i < parts.size(); i++) {
            if (parts.get(i) > parts.get(rootIndex)) {
                rootIndex = i;
            }
        }

        int rootDegree = parts.get(rootIndex);

        parts.remove(rootIndex);

        /*
         * Number the real nodes 0 ... m-1.
         *
         * rootDegree nodes are direct children of the imaginary root.
         *
         * Then attach remaining nodes using available child slots.
         */
        int[] degree = new int[m];

        /*
         * Put larger degrees first. This guarantees that the
         * construction has enough available slots.
         */
        parts.sort(Collections.reverseOrder());

        for (int i = 0; i < parts.size(); i++) {
            degree[i] = parts.get(i);
        }

        @SuppressWarnings("unchecked")
        ArrayList<Integer>[] children = new ArrayList[m];

        for (int i = 0; i < m; i++) {
            children[i] = new ArrayList<>();
        }

        ArrayList<Integer> roots = new ArrayList<>();

        int nextNode = 0;

        /*
         * The imaginary root gets rootDegree children.
         */
        for (int i = 0; i < rootDegree; i++) {
            roots.add(nextNode++);
        }

        /*
         * Queue of nodes whose children we still need to create.
         */
        ArrayDeque<Integer> queue = new ArrayDeque<>();

        for (int v : roots) {
            queue.add(v);
        }

        while (!queue.isEmpty()) {

            int parent = queue.poll();

            int d = degree[parent];

            for (int j = 0; j < d; j++) {

                int child = nextNode++;

                children[parent].add(child);
                queue.add(child);
            }
        }

        /*
         * Encode the forest.
         *
         * A node is:
         *
         *     '(' + children + ')'
         */
        StringBuilder sb = new StringBuilder(2 * m);

        for (int root : roots) {
            build(root, children, sb);
        }

        return sb.toString();
    }

    static void build(
            int node,
            ArrayList<Integer>[] children,
            StringBuilder sb) {

        sb.append('(');

        for (int child : children[node]) {
            build(child, children, sb);
        }

        sb.append(')');
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        precompute();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();
            int k = fs.nextInt();

            /*
             * Balanced parentheses must have even length.
             */
            if ((n & 1) != 0) {
                out.append("impossible\n");
                continue;
            }

            int m = n / 2;

            /*
             * Every pair () gives at least one balanced substring.
             *
             * Minimum = m
             *
             * Maximum = m(m+1)/2
             */
            int maxK = m * (m + 1) / 2;

            if (k < m || k > maxK) {
                out.append("impossible\n");
                continue;
            }

            int extra = k - m;

            if (prevPart[m][extra] == 0) {
                out.append("impossible\n");
                continue;
            }

            String answer = construct(m, extra);

            if (answer == null || answer.length() != n) {
                out.append("impossible\n");
            } else {
                out.append(answer).append('\n');
            }
        }

        System.out.print(out);
    }

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
                result = result * 10 + c - '0';
                c = read();
            }

            return result * sign;
        }
    }
}



