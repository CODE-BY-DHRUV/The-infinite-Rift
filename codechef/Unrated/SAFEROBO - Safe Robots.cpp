import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            String s = br.readLine().trim();

            StringTokenizer st = new StringTokenizer(br.readLine());
            long sa = Long.parseLong(st.nextToken());
            long sb = Long.parseLong(st.nextToken());

            int a = s.indexOf('A');
            int b = s.indexOf('B');

            int n = s.length();

            /*
             * Alice can make a move while:
             * a + t * sa < n
             *
             * Bob can make a move while:
             * b - t * sb >= 0
             *
             * The simulation at time t is possible only while
             * both robots have successfully made their t-th move.
             *
             * For a collision at time t:
             *
             * a + t*sa = b - t*sb
             *
             * => t = (b-a)/(sa+sb)
             */

            long distance = b - a;
            long speedSum = sa + sb;

            boolean unsafe = false;

            if (distance % speedSum == 0) {
                long t = distance / speedSum;

                /*
                 * t = 0 would mean they were initially
                 * on the same cell, but the statement guarantees
                 * A is to the left of B, so t > 0.
                 *
                 * Check that both robots can actually reach
                 * their collision positions before the simulation
                 * terminates.
                 */
                long alicePos = a + t * sa;
                long bobPos = b - t * sb;

                if (alicePos >= 0 && alicePos < n &&
                    bobPos >= 0 && bobPos < n) {

                    unsafe = true;
                }
            }

            out.append(unsafe ? "unsafe\n" : "safe\n");
        }

        System.out.print(out);
    }
}