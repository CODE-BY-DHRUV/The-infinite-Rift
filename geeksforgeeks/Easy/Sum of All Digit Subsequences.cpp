
class Solution {
    public int subsequenceSum(String s) {
        long MOD = 1000000007L;
        long sum = 0;

        for (int i = 0; i < s.length(); i++) {
            sum = (sum + (s.charAt(i) - '0')) % MOD;
        }

        long power = modPow(2, s.length() - 1, MOD);

        return (int) ((sum * power) % MOD);
    }

    private long modPow(long base, int exp, long mod) {
        long result = 1;

        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % mod;
            }

            base = (base * base) % mod;
            exp >>= 1;
        }

        return result;
    }
}

