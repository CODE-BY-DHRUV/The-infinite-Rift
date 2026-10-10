
class Solution {
    public boolean balancePan(int a, int b) {
        while (b > 0) {
            int rem = b % a;
            b /= a;

            if (rem == 0 || rem == 1) {
                continue;
            }

            if (rem == a - 1) {
                b++;
            } else {
                return false;
            }
        }

        return true;
    }
}
