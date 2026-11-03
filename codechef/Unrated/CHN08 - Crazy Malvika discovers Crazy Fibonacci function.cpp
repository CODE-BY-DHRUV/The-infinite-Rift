import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());

        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            long a = Long.parseLong(st.nextToken());
            long b = Long.parseLong(st.nextToken());
            long n = Long.parseLong(st.nextToken());

            a = (a % MOD + MOD) % MOD;
            b = (b % MOD + MOD) % MOD;

            int pos = (int) ((n - 1) % 6);

            long ans;

            switch (pos) {
                case 0:
                    ans = a;
                    break;

                case 1:
                    ans = b;
                    break;

                case 2:
                    ans = (b - a + MOD) % MOD;
                    break;

                case 3:
                    ans = (MOD - a) % MOD;
                    break;

                case 4:
                    ans = (MOD - b) % MOD;
                    break;

                default:
                    ans = (a - b + MOD) % MOD;
                    break;
            }

            sb.append(ans).append('\n');
        }

        System.out.print(sb);
    }
}
