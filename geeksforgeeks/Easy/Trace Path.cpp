class Solution {
    public boolean isPossible(int n, int m, String s) {
        int row = 0, col = 0;
        int minRow = 0, maxRow = 0;
        int minCol = 0, maxCol = 0;

        for (char c : s.toCharArray()) {
            if (c == 'L') {
                col--;
            } else if (c == 'R') {
                col++;
            } else if (c == 'D') {
                row--;
            } else if (c == 'U') {
                row++;
            }

            minRow = Math.min(minRow, row);
            maxRow = Math.max(maxRow, row);
            minCol = Math.min(minCol, col);
            maxCol = Math.max(maxCol, col);
        }

        return (maxRow - minRow < n) &&
               (maxCol - minCol < m);
    }
}