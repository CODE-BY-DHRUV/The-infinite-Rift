class Solution {
    public String lexiString(String s) {
        int n = s.length();

        int i = 0;
        int j = 1;
        int k = 0;

        while (i < n && j < n && k < n) {
            char a = s.charAt((i + k) % n);
            char b = s.charAt((j + k) % n);

            if (a == b) {
                k++;
            } 
            else if (a > b) {
                i = i + k + 1;

                if (i <= j) {
                    i = j + 1;
                }

                k = 0;
            } 
            else {
                j = j + k + 1;

                if (j <= i) {
                    j = i + 1;
                }

                k = 0;
            }
        }

        int start = Math.min(i, j);

        return s.substring(start) + s.substring(0, start);
    }
}