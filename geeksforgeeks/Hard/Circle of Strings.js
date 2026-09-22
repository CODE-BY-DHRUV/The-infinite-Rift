class Solution {
    public boolean isCircle(String arr[]) {
        int[] in = new int[26];
        int[] out = new int[26];

        // Adjacency matrix for connectivity
        boolean[][] graph = new boolean[26][26];

        for (String s : arr) {
            int first = s.charAt(0) - 'a';
            int last = s.charAt(s.length() - 1) - 'a';

            out[first]++;
            in[last]++;

            graph[first][last] = true;
            graph[last][first] = true; // for undirected connectivity
        }

        // Condition 1: indegree must equal outdegree
        for (int i = 0; i < 26; i++) {
            if (in[i] != out[i]) {
                return false;
            }
        }

        // Find a vertex that actually occurs
        int start = -1;
        for (int i = 0; i < 26; i++) {
            if (in[i] + out[i] > 0) {
                start = i;
                break;
            }
        }

        // At least one string exists, so start will exist
        if (start == -1) {
            return false;
        }

        // Condition 2: all used vertices must be connected
        boolean[] visited = new boolean[26];
        dfs(start, graph, visited);

        for (int i = 0; i < 26; i++) {
            if (in[i] + out[i] > 0 && !visited[i]) {
                return false;
            }
        }

        return true;
    }

    private void dfs(int node, boolean[][] graph, boolean[] visited) {
        visited[node] = true;

        for (int i = 0; i < 26; i++) {
            if (graph[node][i] && !visited[i]) {
                dfs(i, graph, visited);
            }
        }
    }
}