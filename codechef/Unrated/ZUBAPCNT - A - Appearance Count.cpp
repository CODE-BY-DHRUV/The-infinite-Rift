
import java.io.*;

public class Main {
    static final long MOD = 1_000_000_007L;

    static long modPow(long base, int exp) {
        long result = 1;

        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = result * base % MOD;
            }

            base = base * base % MOD;
            exp >>= 1;
        }

        return result;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        StringBuilder out = new StringBuilder();
        int T = Integer.parseInt(br.readLine().trim());

        for (int tc = 1; tc <= T; tc++) {
            String[] first = br.readLine().trim().split("\\s+");
            int n = Integer.parseInt(first[0]);
            int m = Integer.parseInt(first[1]);

            out.append("Case ").append(tc).append(":\n");

            for (int i = 0; i < m; i++) {
                String s = br.readLine().trim();
                int k = s.length();

                long ans = 0;

                if (k <= n) {
                    ans = ((long) (n - k + 1)
                           * modPow(26, n - k)) % MOD;
                }

                out.append(ans).append('\n');
            }
        }

        System.out.print(out);
    }
}
