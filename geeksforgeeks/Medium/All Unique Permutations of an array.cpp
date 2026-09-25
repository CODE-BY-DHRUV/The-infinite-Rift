class Solution {

    public ArrayList<ArrayList<Integer>> uniquePerms(int[] arr) {
        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();

        Arrays.sort(arr);

        boolean[] used = new boolean[arr.length];
        ArrayList<Integer> current = new ArrayList<>();

        solve(arr, used, current, ans);

        return ans;
    }

    void solve(int[] arr, boolean[] used,
               ArrayList<Integer> current,
               ArrayList<ArrayList<Integer>> ans) {

        if (current.size() == arr.length) {
            ans.add(new ArrayList<>(current));
            return;
        }

        for (int i = 0; i < arr.length; i++) {

            if (used[i]) {
                continue;
            }

            // Skip duplicate values at the same level
            if (i > 0 && arr[i] == arr[i - 1] && !used[i - 1]) {
                continue;
            }

            used[i] = true;
            current.add(arr[i]);

            solve(arr, used, current, ans);

            // Backtrack
            current.remove(current.size() - 1);
            used[i] = false;
        }
    }
}