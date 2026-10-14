
class Solution {
    public int maxValue(int n) {
        while ((n & (n >> 1) & (n >> 2)) != 0) {
            int mask = n & (n >> 1) & (n >> 2);
            int bit = 31 - Integer.numberOfLeadingZeros(mask);
            n &= ~(1 << bit);
        }
        return n;
    }
}
