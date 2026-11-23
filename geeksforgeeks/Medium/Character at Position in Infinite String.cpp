

class Solution {
    public char posInfinite(String s, int pos) {
        long len = s.length();
        long step = 1;

        // Build lengths until pos is covered
        while (len < pos) {
            len = 2 * len + step;
            step++;
        }

        // Current separator count
        step--;

        // Reverse the construction
        while (len > s.length()) {
            long oldLen = (len - step) / 2;

            if (pos <= oldLen) {
                len = oldLen;
            } 
            else if (pos <= oldLen + step) {
                return '$';
            } 
            else {
                pos = (int)(len - pos + 1);
                len = oldLen;
            }

            step--;
        }

        return s.charAt(pos - 1);
    }
}


