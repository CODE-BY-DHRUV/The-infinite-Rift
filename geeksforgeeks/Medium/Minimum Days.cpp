
class Solution {

    boolean check(String s, int[] p, int days) {
        int n = s.length();
        boolean[] removed = new boolean[n];

        for (int i = 0; i < days; i++) {
            removed[p[i]] = true;
        }

        for (int i = 0; i < n - 1; i++) {
            if (!removed[i] && !removed[i + 1]
                    && s.charAt(i) == s.charAt(i + 1)) {
                return false;
            }
        }

        return true;
    }

    public int getMinimumDays(String S, int[] P) {
        int n = S.length();

        int low = 0, high = n;
        int ans = n;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (check(S, P, mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
}
