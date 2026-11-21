
class Solution {
    public int minFlips(String s) {
        int flips1 = 0;
        int flips2 = 0;

        for (int i = 0; i < s.length(); i++) {

            // Pattern 1: 010101...
            if (s.charAt(i) != (i % 2 == 0 ? '0' : '1')) {
                flips1++;
            }

            // Pattern 2: 101010...
            if (s.charAt(i) != (i % 2 == 0 ? '1' : '0')) {
                flips2++;
            }
        }

        return Math.min(flips1, flips2);
    }
}
