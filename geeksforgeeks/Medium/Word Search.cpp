class Solution {

    int n, m;
    int[] dr = {-1, 1, 0, 0};
    int[] dc = {0, 0, -1, 1};

    public boolean isWordExist(char[][] mat, String word) {

        n = mat.length;
        m = mat[0].length;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                if (mat[i][j] == word.charAt(0)) {
                    if (dfs(mat, word, i, j, 0)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    private boolean dfs(char[][] mat, String word,
                        int r, int c, int index) {

        // All characters matched
        if (index == word.length()) {
            return true;
        }

        // Out of bounds
        if (r < 0 || r >= n || c < 0 || c >= m) {
            return false;
        }

        // Current character doesn't match
        if (mat[r][c] != word.charAt(index)) {
            return false;
        }

        // Mark current cell as visited
        char original = mat[r][c];
        mat[r][c] = '#';

        // Try all 4 directions
        for (int d = 0; d < 4; d++) {

            int nr = r + dr[d];
            int nc = c + dc[d];

            if (dfs(mat, word, nr, nc, index + 1)) {

                // Restore before returning
                mat[r][c] = original;
                return true;
            }
        }

        // Backtrack: restore the cell
        mat[r][c] = original;

        return false;
    }
}