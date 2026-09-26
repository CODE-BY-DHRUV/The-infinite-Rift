import java.util.*;

class Solution {
    public ArrayList<Integer> repeatedRows(int[][] mat) {
        ArrayList<Integer> ans = new ArrayList<>();
        HashSet<String> set = new HashSet<>();

        for (int i = 0; i < mat.length; i++) {
            StringBuilder row = new StringBuilder();

            for (int j = 0; j < mat[i].length; j++) {
                row.append(mat[i][j]);
            }

            String key = row.toString();

            if (set.contains(key)) {
                ans.add(i);
            } else {
                set.add(key);
            }
        }

        return ans;
    }
}