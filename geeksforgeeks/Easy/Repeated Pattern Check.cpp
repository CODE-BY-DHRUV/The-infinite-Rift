
class Solution {
    public boolean findPattern(String s) {
        int i = 0;
        int n = s.length();

        while (i < n) {
            if (s.charAt(i) != 'x') {
                return false;
            }

            int xCount = 0;
            while (i < n && s.charAt(i) == 'x') {
                xCount++;
                i++;
            }

            int yCount = 0;
            while (i < n && s.charAt(i) == 'y') {
                yCount++;
                i++;
            }

            if (xCount != yCount) {
                return false;
            }
        }

        return true;
    }
}
