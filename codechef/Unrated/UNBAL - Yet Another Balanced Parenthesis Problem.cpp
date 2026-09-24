
import java.io.*;
import java.util.*;

public class Main {

    // Creates a primitive balanced parenthesis string of length len.
    // Example:
    // len = 2 -> ()
    // len = 4 -> (())
    // len = 6 -> ((()))
    static void addBlock(StringBuilder sb, int len) {
        int half = len / 2;

        for (int i = 0; i < half; i++) {
            sb.append('(');
        }

        for (int i = 0; i < half; i++) {
            sb.append(')');
        }
    }

    static String solve(int n, int k) {

        // Impossible cases.
        if (k == 2 || k == 4 || k == n) {
            return "-1";
        }

        /*
         * Case 1:
         * k = 2 (mod 4)
         *
         * Use:
         *     (())(())(())...
         *
         * Every primitive block has length 4.
         * Hence every balanced substring has length 2, 4,
         * or a multiple of 4.
         *
         * Since k >= 6 and k % 4 == 2, k cannot occur.
         */
        if (k % 4 == 2) {

            StringBuilder ans = new StringBuilder(n);

            if (n % 4 == 0) {
                for (int i = 0; i < n / 4; i++) {
                    ans.append("(())");
                }
            } else {
                /*
                 * n % 4 == 2.
                 *
                 * Put an outer pair around the (()) blocks:
                 *
                 * ( (()) (()) ... )
                 *
                 * Example:
                 * n = 10 -> ((())(()))
                 */
                ans.append('(');

                for (int i = 0; i < (n - 2) / 4; i++) {
                    ans.append("(())");
                }

                ans.append(')');
            }

            return ans.toString();
        }

        /*
         * Case 2:
         * k % 4 == 0
         *
         * Let L = k - 2.
         *
         * L < k, so a block of length L cannot itself contain
         * a balanced substring of length k.
         *
         * We arrange the blocks so that no consecutive blocks
         * have total length k.
         */
        int L = k - 2;

        int q = n / L;
        int r = n % L;

        StringBuilder ans = new StringBuilder(n);

        if (r == 0) {

            // n = q * (k - 2)
            //
            // Since 2L > k for k > 4, two consecutive blocks
            // already have length > k.
            for (int i = 0; i < q; i++) {
                addBlock(ans, L);
            }

        } else if (r != 2) {

            /*
             * n = q*L + r, where r != 2.
             *
             * Since r < L = k-2:
             *
             * r + L != k
             *
             * because r != 2.
             */
            for (int i = 0; i < q; i++) {
                addBlock(ans, L);
            }

            addBlock(ans, r);

        } else {

            /*
             * The dangerous case:
             *
             * n = q*L + 2
             *
             * because:
             *
             *     L + 2 = k
             *
             * So we cannot simply append a block of length 2.
             *
             * We use:
             *
             *   L ... L, 4, L, 4, (k-8)
             *
             * where there are q-2 copies of L.
             *
             * Total:
             *
             * (q-2)L + 4 + L + 4 + (k-8)
             * = qL + 2
             *
             * No consecutive block sum is k.
             */

            for (int i = 0; i < q - 2; i++) {
                addBlock(ans, L);
            }

            addBlock(ans, 4);
            addBlock(ans, L);
            addBlock(ans, 4);

            if (k - 8 > 0) {
                addBlock(ans, k - 8);
            }
        }

        return ans.toString();
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br =
                new BufferedReader(new InputStreamReader(System.in));

        StringBuilder output = new StringBuilder();

        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {

            StringTokenizer st =
                    new StringTokenizer(br.readLine());

            int n = Integer.parseInt(st.nextToken());
            int k = Integer.parseInt(st.nextToken());

            output.append(solve(n, k)).append('\n');
        }

        System.out.print(output);
    }
}

