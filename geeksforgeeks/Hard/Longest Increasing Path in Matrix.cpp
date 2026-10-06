import java.util.*;

class Solution {

    static class Cell {
        int value;
        int row;
        int col;

        Cell(int value, int row, int col) {
            this.value = value;
            this.row = row;
            this.col = col;
        }
    }

    public int longIncPath(int[][] matrix, int n, int m) {
        int total = n * m;

        Cell[] cells = new Cell[total];
        int index = 0;

        // Store all cells
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cells[index++] = new Cell(matrix[i][j], i, j);
            }
        }

        // Sort cells by value
        Arrays.sort(cells, Comparator.comparingInt(a -> a.value));

        int[][] dp = new int[n][m];

        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        int answer = 1;

        for (Cell cell : cells) {
            int r = cell.row;
            int c = cell.col;

            // Path containing only this cell
            dp[r][c] = 1;

            // Check four directions
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr >= 0 && nr < n &&
                    nc >= 0 && nc < m &&
                    matrix[nr][nc] < matrix[r][c]) {

                    dp[r][c] = Math.max(
                        dp[r][c],
                        dp[nr][nc] + 1
                    );
                }
            }

            answer = Math.max(answer, dp[r][c]);
        }

        return answer;
    }
}