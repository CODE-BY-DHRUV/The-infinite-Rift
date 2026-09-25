class Solution {

    public ArrayList<ArrayList<Integer>> combinationSum(int n, int k) {
        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();
        ArrayList<Integer> current = new ArrayList<>();

        solve(1, n, k, current, ans);

        return ans;
    }

    void solve(int start, int target, int k,
               ArrayList<Integer> current,
               ArrayList<ArrayList<Integer>> ans) {

        // Found a valid combination
        if (k == 0) {
            if (target == 0) {
                ans.add(new ArrayList<>(current));
            }
            return;
        }

        // No valid combination possible
        if (target <= 0) {
            return;
        }

        // Try numbers from start to 9
        for (int i = start; i <= 9; i++) {

            // Choose
            current.add(i);

            // Move to i + 1 so that i cannot be reused
            solve(i + 1, target - i, k - 1, current, ans);

            // Backtrack
            current.remove(current.size() - 1);
        }
    }
}