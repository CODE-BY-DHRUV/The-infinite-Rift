import java.util.*;

class Solution {
    public int minTime(int[] duration, int[][] dependencies) {
        int n = duration.length;

        List<List<Integer>> graph = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }

        int[] indegree = new int[n];

        // Build graph: u -> v
        for (int[] edge : dependencies) {
            int u = edge[0];
            int v = edge[1];

            graph.get(u).add(v);
            indegree[v]++;
        }

        // dp[i] = earliest completion time of module i
        long[] dp = new long[n];

        Queue<Integer> queue = new ArrayDeque<>();

        // Modules with no dependencies can start immediately
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                dp[i] = duration[i];
                queue.offer(i);
            }
        }

        int processed = 0;
        long answer = 0;

        while (!queue.isEmpty()) {
            int u = queue.poll();
            processed++;

            answer = Math.max(answer, dp[u]);

            for (int v : graph.get(u)) {

                // v starts after u finishes
                dp[v] = Math.max(dp[v],
                                 dp[u] + duration[v]);

                indegree[v]--;

                if (indegree[v] == 0) {
                    queue.offer(v);
                }
            }
        }

        // Cycle exists
        if (processed != n) {
            return -1;
        }

        return (int) answer;
    }
}