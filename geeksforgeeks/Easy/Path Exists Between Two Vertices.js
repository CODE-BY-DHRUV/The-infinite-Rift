
import java.util.*;

class Solution {
    boolean checkPath(ArrayList<ArrayList<Integer>> adj, int src, int dest) {

        int V = adj.size();

        boolean[] visited = new boolean[V];
        Queue<Integer> q = new LinkedList<>();

        q.offer(src);
        visited[src] = true;

        while (!q.isEmpty()) {
            int node = q.poll();

            if (node == dest) {
                return true;
            }

            for (int next : adj.get(node)) {
                if (!visited[next]) {
                    visited[next] = true;
                    q.offer(next);
                }
            }
        }

        return false;
    }
}
