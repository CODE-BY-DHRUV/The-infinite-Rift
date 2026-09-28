class Solution {
    public int minStepToReachTarget(int[] knightPos, int[] targetPos, int n) {

        // Already at target
        if (knightPos[0] == targetPos[0] &&
            knightPos[1] == targetPos[1]) {
            return 0;
        }

        int[][] moves = {
            {2, 1}, {2, -1},
            {-2, 1}, {-2, -1},
            {1, 2}, {1, -2},
            {-1, 2}, {-1, -2}
        };

        boolean[][] visited = new boolean[n + 1][n + 1];

        // Queue stores: {row, col, distance}
        java.util.Queue<int[]> queue = new java.util.LinkedList<>();

        int sr = knightPos[0];
        int sc = knightPos[1];

        queue.offer(new int[]{sr, sc, 0});
        visited[sr][sc] = true;

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();

            int r = curr[0];
            int c = curr[1];
            int dist = curr[2];

            for (int[] move : moves) {
                int nr = r + move[0];
                int nc = c + move[1];

                // Check if inside board
                if (nr >= 1 && nr <= n && nc >= 1 && nc <= n
                        && !visited[nr][nc]) {

                    // Target reached
                    if (nr == targetPos[0] && nc == targetPos[1]) {
                        return dist + 1;
                    }

                    visited[nr][nc] = true;
                    queue.offer(new int[]{nr, nc, dist + 1});
                }
            }
        }

        return -1;
    }
}