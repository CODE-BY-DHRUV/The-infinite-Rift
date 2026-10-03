import java.util.*;

class Solution {

    public ArrayList<ArrayList<Integer>> formCoils(int n) {
        int N = 4 * n;

        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();
        ArrayList<Integer> coil1 = new ArrayList<>();
        ArrayList<Integer> coil2 = new ArrayList<>();

        // Create matrix
        int[][] a = new int[N][N];
        int x = 1;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = x++;
            }
        }

        int top = 0;
        int bottom = N - 1;
        int left = 0;
        int right = N - 1;

        while (top <= bottom && left <= right) {

            // -------------------------
            // COIL 1
            // -------------------------

            // Down on left boundary
            for (int i = top; i <= bottom; i++) {
                coil1.add(a[i][left]);
            }

            // Right on bottom boundary
            for (int j = left + 1; j < right; j++) {
                coil1.add(a[bottom][j]);
            }

            // Up on the column just inside right boundary
            for (int i = bottom - 1; i > top; i--) {
                coil1.add(a[i][right - 1]);
            }

            // Left on the row just below top
            for (int j = right - 2; j > left + 1; j--) {
                coil1.add(a[top + 1][j]);
            }


            // -------------------------
            // COIL 2
            // -------------------------

            // Up on right boundary
            for (int i = bottom; i >= top; i--) {
                coil2.add(a[i][right]);
            }

            // Left on top boundary
            for (int j = right - 1; j > left; j--) {
                coil2.add(a[top][j]);
            }

            // Down on column just inside left boundary
            for (int i = top + 1; i < bottom; i++) {
                coil2.add(a[i][left + 1]);
            }

            // Right on row just above bottom
            for (int j = left + 2; j < right - 1; j++) {
                coil2.add(a[bottom - 1][j]);
            }


            // Move two cells inward
            top += 2;
            bottom -= 2;
            left += 2;
            right -= 2;
        }

        ans.add(coil1);
        ans.add(coil2);

        return ans;
    }
}