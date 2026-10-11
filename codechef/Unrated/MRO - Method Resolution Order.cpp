
import java.io.*;

public class Main {
    static final long MOD = 1_000_000_007L;
    static final int MAX = 100000;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());

        int[] queries = new int[T];
        int maxN = 1;

        for (int i = 0; i < T; i++) {
            queries[i] = Integer.parseInt(br.readLine().trim());
            maxN = Math.max(maxN, queries[i]);
        }

        long[] ans = new long[maxN + 1];
        ans[1] = 1;

        long power = 1;

        for (int i = 2; i <= maxN; i++) {
            power = (power * 2) % MOD;
            ans[i] = (ans[i - 1] * (power - 1 + MOD) % MOD);
        }

        StringBuilder out = new StringBuilder();

        for (int n : queries) {
            out.append(ans[n]).append('\n');
        }

        System.out.print(out);
    }
}
