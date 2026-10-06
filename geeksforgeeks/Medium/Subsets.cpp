class Solution {

    ArrayList<ArrayList<Integer>> result = new ArrayList<>();

    public ArrayList<ArrayList<Integer>> subsets(int[] arr) {
        result.clear();

        backtrack(arr, 0, new ArrayList<>());

        return result;
    }

    private void backtrack(int[] arr, int index,
                            ArrayList<Integer> current) {

        // Every state represents a valid subset
        result.add(new ArrayList<>(current));

        // Try including each remaining element
        for (int i = index; i < arr.length; i++) {

            // Include arr[i]
            current.add(arr[i]);

            // Process remaining elements
            backtrack(arr, i + 1, current);

            // Backtrack
            current.remove(current.size() - 1);
        }
    }
}