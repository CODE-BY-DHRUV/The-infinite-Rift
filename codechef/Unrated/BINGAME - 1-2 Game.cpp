import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());

            StringTokenizer st = new StringTokenizer(br.readLine());

            int cnt0 = 0; // Ai % 3 == 0
            int cnt1 = 0; // Ai % 3 == 1
            int cnt2 = 0; // Ai % 3 == 2

            for (int i = 0; i < n; i++) {
                int x = Integer.parseInt(st.nextToken());

                if (x % 3 == 0) {
                    cnt0++;
                } else if (x % 3 == 1) {
                    cnt1++;
                } else {
                    cnt2++;
                }
            }

            int ans;

            // All elements are divisible by 3
            if (cnt0 == n) {
                ans = 0;
            }
            // Exactly one element is 1 mod 3,
            // exactly one is 2 mod 3,
            // and all others are 0 mod 3.
            else if (cnt1 == 1 && cnt2 == 1 && cnt0 == n - 2) {
                ans = n - 1;
            }
            // Every first move is winning
            else {
                ans = n;
            }

            out.append(ans).append('\n');
        }

        System.out.print(out);
    }
}
