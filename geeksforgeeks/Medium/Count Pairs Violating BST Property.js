import java.util.*;

class Solution {
    long ans = 0;

    public long pairsViolatingBST(Node root) {
        ans = 0;
        solve(root);
        return ans;
    }

    ArrayList<Integer> solve(Node root) {
        ArrayList<Integer> vals = new ArrayList<>();

        if (root == null) return vals;

        ArrayList<Integer> left = solve(root.left);
        ArrayList<Integer> right = solve(root.right);

        // Violations between the current node and left subtree
        for (int x : left) {
            if (x > root.data) ans++;
        }

        // Violations between the current node and right subtree
        for (int x : right) {
            if (x < root.data) ans++;
        }

        // Count cross-subtree violations efficiently
        int i = 0, j = 0;
        while (i < left.size() && j < right.size()) {
            if (left.get(i) <= right.get(j)) {
                i++;
            } else {
                ans += left.size() - i;
                j++;
            }
        }

        // Merge and sort the values
        vals.addAll(left);
        vals.addAll(right);
        vals.add(root.data);
        Collections.sort(vals);

        return vals;
    }
}