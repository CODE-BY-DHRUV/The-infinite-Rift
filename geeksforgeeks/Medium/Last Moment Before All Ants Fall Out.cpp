class Solution {
    public int getLastMoment(int n, int[] left, int[] right) {

        int ans = 0;

        // Ants moving left fall at their position.
        for (int pos : left) {
            ans = Math.max(ans, pos);
        }

        // Ants moving right fall at n.
        // Time = n - position.
        for (int pos : right) {
            ans = Math.max(ans, n - pos);
        }

        return ans;
    }
}