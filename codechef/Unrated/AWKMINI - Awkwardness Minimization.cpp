import java.io.*;
import java.io.*;

public class Main {

    static long solve(String s) {
        int n = s.length();

        int B = 0;
        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == 'b') {
                B++;
            }
        }

        int G = n - B;

        long ans = 0;

        // Consider every boundary k | k+1
        for (int k = 1; k < n; k++) {

            // x is the number of boys in the first k positions.
            //
            // Optimal real-valued x:
            // x = (2*k + B - G) / 4
            //
            // Round to nearest integer.
            int numerator = 2 * k + B - G;

            int x = Math.floorDiv(numerator + 2, 4);

            // x must be feasible:
            // At most k boys can be on the left.
            // At most B boys exist.
            int low = Math.max(0, k - G);
            int high = Math.min(k, B);

            if (x < low) {
                x = low;
            } else if (x > high) {
                x = high;
            }

            // Contribution of this boundary:
            //
            // boys-left    * girls-right
            // +
            // girls-left   * boys-right
            //
            long boysLeft = x;
            long girlsLeft = k - x;
            long boysRight = B - x;
            long girlsRight = G - girlsLeft;

            ans += boysLeft * girlsRight
                 + girlsLeft * boysRight;
        }

        return ans;
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br =
                new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            String s = br.readLine().trim();
            out.append(solve(s)).append('\n');
        }

        System.out.print(out);
    }
}