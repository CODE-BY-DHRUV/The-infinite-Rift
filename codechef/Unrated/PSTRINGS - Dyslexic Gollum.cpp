
import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    static boolean isPalindrome(int mask, int len) {

        int left = 0;
        int right = len - 1;

        while (left < right) {

            int a = (mask >> left) & 1;
            int b = (mask >> right) & 1;

            if (a != b) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }

    static long solve(int n, int k) {

        int size = 1 << k;
        int fullMask = size - 1;

        long[] dp = new long[size];
        long[] next = new long[size];

        dp[0] = 1;

        for (int len = 0; len < n; len++) {

            Arrays.fill(next, 0);

            for (int mask = 0; mask < size; mask++) {

                if (dp[mask] == 0) {
                    continue;
                }

                for (int bit = 0; bit <= 1; bit++) {

                    // Check palindrome of length K
                    if (len >= k - 1) {

                        int suffixK =
                                ((mask & ((1 << (k - 1)) - 1)) << 1) | bit;

                        if (isPalindrome(suffixK, k)) {
                            continue;
                        }
                    }

                    // Check palindrome of length K + 1
                    if (len >= k) {

                        int suffixK1 = (mask << 1) | bit;

                        if (isPalindrome(suffixK1, k + 1)) {
                            continue;
                        }
                    }

                    int newMask = ((mask << 1) | bit) & fullMask;

                    next[newMask] =
                            (next[newMask] + dp[mask]) % MOD;
                }
            }

            long[] temp = dp;
            dp = next;
            next = temp;
        }

        long answer = 0;

        for (long value : dp) {
            answer = (answer + value) % MOD;
        }

        return answer;
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner(System.in);

        int t = fs.nextInt();

        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {

            int n = fs.nextInt();
            int k = fs.nextInt();

            sb.append(solve(n, k)).append('\n');
        }

        System.out.print(sb);
    }

    static class FastScanner {

        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];

        private int ptr = 0;
        private int len = 0;

        FastScanner(InputStream in) {
            this.in = in;
        }

        private int read() throws IOException {

            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;

                if (len <= 0) {
                    return -1;
                }
            }

            return buffer[ptr++];
        }

        int nextInt() throws IOException {

            int c;

            do {
                c = read();
            } while (c <= ' ' && c != -1);

            int num = 0;

            while (c > ' ') {
                num = num * 10 + c - '0';
                c = read();
            }

            return num;
        }
    }
}
