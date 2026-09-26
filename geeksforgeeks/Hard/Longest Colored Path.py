import java.util.*;

class Solution {

    public int longestPath(String s, int[][] edges) {

        int n = s.length();

        ArrayList<Integer>[] graph = new ArrayList[n];

        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }

        for (int[] e : edges) {
            int u = e[0] - 1;
            int v = e[1] - 1;

            graph[u].add(v);
            graph[v].add(u);
        }

        /*
         * Root the tree at node 0.
         */
        int[] parent = new int[n];
        Arrays.fill(parent, -1);

        int[] order = new int[n];
        int index = 0;

        ArrayDeque<Integer> queue = new ArrayDeque<>();
        queue.add(0);
        parent[0] = -2;

        while (!queue.isEmpty()) {

            int u = queue.poll();
            order[index++] = u;

            for (int v : graph[u]) {

                if (v == parent[u]) {
                    continue;
                }

                if (parent[v] != -1) {
                    continue;
                }

                parent[v] = u;
                queue.add(v);
            }
        }

        /*
         * down[u]:
         * Maximum number of EDGES in a same-color path
         * starting at u and going into its subtree.
         *
         * Example:
         *
         * R
         * |
         * R
         * |
         * R
         *
         * down[top R] = 2
         */
        int[] down = new int[n];

        /*
         * Calculate down[] bottom-up.
         */
        for (int i = n - 1; i >= 0; i--) {

            int u = order[i];

            for (int v : graph[u]) {

                if (parent[v] != u) {
                    continue;
                }

                // Child has same color
                if (s.charAt(u) == s.charAt(v)) {

                    down[u] = Math.max(
                        down[u],
                        down[v] + 1
                    );
                }
            }
        }

        /*
         * up[u]:
         * Maximum number of EDGES in a same-color path
         * starting at u and going through its parent side.
         *
         * We need the best child excluding the child itself
         * when calculating the path through the parent.
         */
        int[] up = new int[n];

        /*
         * Process top-down.
         */
        for (int i = 0; i < n; i++) {

            int u = order[i];

            /*
             * Find the largest and second-largest
             * same-color child contributions.
             */
            int best1 = -1;
            int best2 = -1;
            int bestChild = -1;

            for (int v : graph[u]) {

                if (parent[v] != u) {
                    continue;
                }

                if (s.charAt(u) != s.charAt(v)) {
                    continue;
                }

                int value = down[v] + 1;

                if (value > best1) {
                    best2 = best1;
                    best1 = value;
                    bestChild = v;
                } else if (value > best2) {
                    best2 = value;
                }
            }

            /*
             * Calculate up[] for each child.
             */
            for (int v : graph[u]) {

                if (parent[v] != u) {
                    continue;
                }

                if (s.charAt(u) != s.charAt(v)) {
                    continue;
                }

                /*
                 * A path from v through u can use:
                 *
                 * 1. up[u]
                 * 2. u's other child
                 *
                 * But it cannot use v's own subtree.
                 */
                int bestFromU = up[u];

                if (bestChild == v) {
                    bestFromU = Math.max(bestFromU, best2);
                } else {
                    bestFromU = Math.max(bestFromU, best1);
                }

                up[v] = bestFromU + 1;
            }
        }

        /*
         * eccentricity[u] =
         * longest same-color distance from u.
         */
        int answer = 1;

        for (int u = 0; u < n; u++) {

            int eccentricity = Math.max(up[u], down[u]);

            /*
             * Number of nodes = number of edges + 1
             */
            answer = Math.max(answer, eccentricity + 1);
        }

        /*
         * Now consider paths containing BOTH colors.
         *
         * A valid path must be:
         *
         * R R R B B B
         *
         * Therefore there is exactly ONE R-B edge.
         *
         * For every R-B edge (u,v):
         *
         *     best same-color part at u
         *   + connecting edge
         *   + best same-color part at v
         *
         * Since eccentricity[] is in edges:
         *
         *     ecc[u] + 1 + 1 + ecc[v]
         *
         * =   ecc[u] + ecc[v] + 2 nodes
         */
        for (int u = 0; u < n; u++) {

            int eccU = Math.max(up[u], down[u]);

            for (int v : graph[u]) {

                /*
                 * Process every edge only once.
                 */
                if (u > v) {
                    continue;
                }

                if (s.charAt(u) != s.charAt(v)) {

                    int eccV = Math.max(up[v], down[v]);

                    int candidate = eccU + eccV + 2;

                    answer = Math.max(answer, candidate);
                }
            }
        }

        return answer;
    }
}