
class Solution {
    public int goodIndices(int[] arr) {
        int n = arr.length;
        int[] state = new int[n];
        // 0 = unvisited, 1 = visiting, 2 = good, 3 = bad

        int count = 0;

        for (int i = 0; i < n; i++) {
            if (state[i] == 0) {
                count += dfs(i, arr, state);
            }
        }

        return count;
    }

    private int dfs(int start, int[] arr, int[] state) {
        int n = arr.length;
        java.util.ArrayList<Integer> path = new java.util.ArrayList<>();
        int curr = start;

        while (curr >= 0 && curr < n && state[curr] == 0) {
            state[curr] = 1;
            path.add(curr);

            if (arr[curr] == 0) {
                break;
            }

            curr += arr[curr];
        }

        boolean good;

        if (curr < 0 || curr >= n) {
            good = true;
        } else if (state[curr] == 2) {
            good = true;
        } else {
            // Reached a cycle or a bad index
            good = false;
        }

        // Propagate the result backward through the path
        for (int i = path.size() - 1; i >= 0; i--) {
            int node = path.get(i);
            state[node] = good ? 2 : 3;
        }

        // Count only the indices newly classified as good
        int result = 0;
        for (int node : path) {
            if (state[node] == 2) {
                result++;
            }
        }

        return result;
    }
}