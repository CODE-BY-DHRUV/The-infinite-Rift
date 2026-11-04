
import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner();
        StringBuilder sb = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {

            int n = fs.nextInt();

            HashMap<Integer, Integer> freq = new HashMap<>();

            for (int i = 0; i < n; i++) {
                int x = fs.nextInt();
                freq.put(x, freq.getOrDefault(x, 0) + 1);
            }

            // Count occurrences of each marginal value.
            int[] cnt = new int[2 * n + 1];

            for (int k : freq.values()) {

                for (int j = 0; j < k; j++) {

                    int value = k - 1 - 2 * j;

                    cnt[value + n]++;
                }
            }

            // Precompute factorials.
            long[] fact = new long[n + 1];

            fact[0] = 1;

            for (int i = 1; i <= n; i++) {
                fact[i] = (fact[i - 1] * i) % MOD;
            }

            // Calculate the answer.
            long ans = 1;

            for (int i = 0; i <= 2 * n; i++) {

                if (cnt[i] > 0) {
                    ans = (ans * fact[cnt[i]]) % MOD;
                }
            }

            sb.append(ans).append('\n');
        }

        System.out.print(sb);
    }
}

