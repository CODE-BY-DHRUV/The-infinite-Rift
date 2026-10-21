class Solution {
    public int minimumSum(String s) {
        int n = s.length();
        int m = (n + 1) / 2;
        char[] a = new char[m];

        // Check whether a palindrome is possible
        for (int i = 0; i < m; i++) {
            char left = s.charAt(i);
            char right = s.charAt(n - 1 - i);

            if (left != '?' && right != '?' && left != right) {
                return -1;
            }

            a[i] = (left != '?') ? left : right;
        }

        // Fill '?' runs optimally
        int i = 0;
        while (i < m) {
            if (a[i] != '?') {
                i++;
                continue;
            }

            int start = i;
            while (i < m && a[i] == '?') {
                i++;
            }

            if (start > 0 && i < m) {
                char left = a[start - 1];
                char right = a[i];

                for (int j = start; j < i; j++) {
                    a[j] = left;
                }

                // The minimum cost across the gap is |left-right|.
                // Filling with left achieves this.
            } else if (start > 0) {
                for (int j = start; j < i; j++) {
                    a[j] = a[start - 1];
                }
            } else if (i < m) {
                for (int j = start; j < i; j++) {
                    a[j] = a[i];
                }
            } else {
                for (int j = start; j < i; j++) {
                    a[j] = 'a';
                }
            }
        }

        // Calculate cost in the first half
        int sum = 0;
        for (int j = 1; j < m; j++) {
            sum += Math.abs(a[j] - a[j - 1]);
        }

        // Add the center-to-center edge only once for odd lengths.
        if (n % 2 == 1) {
            return 2 * sum;
        }

        return 2 * sum;
    }
}