
class Solution {
    public int largestSumCycle(int[] edge) {
        int n = edge.length;

        boolean[] visited = new boolean[n];
        int maxSum = -1;

        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;

            java.util.HashMap<Integer, Integer> position =
                new java.util.HashMap<>();

            int node = i;

            while (node != -1 && !visited[node]) {
                visited[node] = true;
                position.put(node, position.size());
                node = edge[node];
            }

            if (node != -1 && position.containsKey(node)) {
                int sum = 0;
                int curr = node;

                do {
                    sum += curr;
                    curr = edge[curr];
                } while (curr != node);

                maxSum = Math.max(maxSum, sum);
            }
        }

        return maxSum;
    }
}

