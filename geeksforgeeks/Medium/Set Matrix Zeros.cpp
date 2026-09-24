class Solution {
    public void setMatrixZeroes(int[][] mat) {
        int n = mat.length;
        int m = mat[0].length;

        boolean firstRowZero = false;
        boolean firstColZero = false;

        // Check whether first row contains 0
        for (int j = 0; j < m; j++) {
            if (mat[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }

        // Check whether first column contains 0
        for (int i = 0; i < n; i++) {
            if (mat[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }

        // Use first row and first column as markers
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (mat[i][j] == 0) {
                    mat[i][0] = 0;
                    mat[0][j] = 0;
                }
            }
        }

        // Set marked rows to zero
        for (int i = 1; i < n; i++) {
            if (mat[i][0] == 0) {
                for (int j = 1; j < m; j++) {
                    mat[i][j] = 0;
                }
            }
        }

        // Set marked columns to zero
        for (int j = 1; j < m; j++) {
            if (mat[0][j] == 0) {
                for (int i = 1; i < n; i++) {
                    mat[i][j] = 0;
                }
            }
        }

        // Finally handle first row
        if (firstRowZero) {
            for (int j = 0; j < m; j++) {
                mat[0][j] = 0;
            }
        }

        // Finally handle first column
        if (firstColZero) {
            for (int i = 0; i < n; i++) {
                mat[i][0] = 0;
            }
        }
    }
}