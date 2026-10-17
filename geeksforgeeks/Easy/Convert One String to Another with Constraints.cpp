class Solution {
    public boolean isItPossible(String s1, String s2) {
        int n = s1.length();
        if (n != s2.length()) {
            return false;
        }

        int i = 0, j = 0;

        while (i < n && j < n) {
            // Skip '#' in s1
            while (i < n && s1.charAt(i) == '#') {
                i++;
            }
            // Skip '#' in s2
            while (j < n && s2.charAt(j) == '#') {
                j++;
            }

            // If both reached the end
            if (i == n && j == n) {
                break;
            }

            // If one reached the end while the other didn't
            if (i == n || j == n) {
                return false;
            }

            // Characters must match
            if (s1.charAt(i) != s2.charAt(j)) {
                return false;
            }

            char ch = s1.charAt(i);

            // 'A' can only move left (s1 index >= s2 index)
            if (ch == 'A' && i < j) {
                return false;
            }
            // 'B' can only move right (s1 index <= s2 index)
            if (ch == 'B' && i > j) {
                return false;
            }

            i++;
            j++;
        }

        // Ensure remaining characters in s1 are only '#'
        while (i < n) {
            if (s1.charAt(i) != '#') return false;
            i++;
        }

        // Ensure remaining characters in s2 are only '#'
        while (j < n) {
            if (s2.charAt(j) != '#') return false;
            j++;
        }

        return true;
    }
}