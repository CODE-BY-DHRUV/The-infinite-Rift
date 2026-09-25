class Solution {

    public ArrayList<ArrayList<Integer>> equalPartition(int[] arr) {

        ArrayList<ArrayList<Integer>> ans = new ArrayList<>();

        int n = arr.length;
        int totalSum = 0;

        for (int x : arr) {
            totalSum += x;
        }

        // Equal sums require total sum to be even
        if (totalSum % 2 != 0) {
            return ans;
        }

        int target = totalSum / 2;

        // For even n: choose exactly n/2 elements.
        // For odd n: either size can be (n-1)/2 or (n+1)/2.
        int size1 = n / 2;

        boolean[] used = new boolean[n];
        ArrayList<Integer> first = new ArrayList<>();

        if (find(arr, 0, size1, target, first, used)) {

            ArrayList<Integer> second = new ArrayList<>();

            for (int i = 0; i < n; i++) {
                if (!used[i]) {
                    second.add(arr[i]);
                }
            }

            ans.add(first);
            ans.add(second);
        }

        return ans;
    }

    boolean find(int[] arr, int index, int remaining,
                 int target, ArrayList<Integer> current,
                 boolean[] used) {

        if (remaining == 0) {
            return target == 0;
        }

        if (index == arr.length) {
            return false;
        }

        // Choose current element
        used[index] = true;
        current.add(arr[index]);

        if (find(arr, index + 1, remaining - 1,
                 target - arr[index], current, used)) {
            return true;
        }

        // Backtrack
        current.remove(current.size() - 1);
        used[index] = false;

        // Don't choose current element
        if (find(arr, index + 1, remaining,
                 target, current, used)) {
            return true;
        }

        return false;
    }
}