import java.io.*;
import java.util.*;

public class Main {

    // Returns the two positions (0-indexed) that remain
    // when the Josephus process stops at 2 soldiers.
    static long[] josephusTwo(long n, long k) {
        // Two soldiers are already remaining.
        if (n == 2) {
            return new long[]{0, 1};
        }

        // k = 1: soldiers are removed in increasing order.
        // The last two remaining are n-2 and n-1.
        if (k == 1) {
            return new long[]{n - 2, n - 1};
        }

        /*
         * If k > n, only one person is removed in this step.
         * After removing one person, the problem becomes n-1.
         */
        if (k > n) {
            long[] res = josephusTwo(n - 1, k);

            res[0] = (res[0] + k) % n;
            res[1] = (res[1] + k) % n;

            return res;
        }

        /*
         * When k <= n, we can remove n/k people at once.
         *
         * The remaining problem has:
         *      n - n/k
         * people.
         */
        long removed = n / k;
        long newN = n - removed;

        long[] res = josephusTwo(newN, k);

        res[0] = mapBack(res[0], n, k);
        res[1] = mapBack(res[1], n, k);

        return res;
    }

    /*
     * Maps a position from the reduced problem back
     * to its original position.
     */
    static long mapBack(long pos, long n, long k) {
        pos -= n % k;

        if (pos < 0) {
            pos += n;
        } else {
            pos += pos / (k - 1);
        }

        return pos;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        while (true) {
            String line = br.readLine();
            if (line == null) break;

            line = line.trim();
            if (line.isEmpty()) continue;

            StringTokenizer st = new StringTokenizer(line);

            long n = Long.parseLong(st.nextToken());
            long k = Long.parseLong(st.nextToken());

            if (n == 0 && k == 0) {
                break;
            }

            long[] lastTwo = josephusTwo(n, k);

            /*
             * One of these two is the final survivor.
             * The other one is the last soldier taken to prison.
             *
             * We can identify the survivor using the standard
             * Josephus recurrence.
             */
            long survivor = josephus(n, k);

            long answer;

            if (lastTwo[0] == survivor) {
                answer = lastTwo[1];
            } else {
                answer = lastTwo[0];
            }

            // Convert from 0-indexed position to soldier ID.
            out.append(answer + 1).append('\n');
        }

        System.out.print(out);
    }

    /*
     * Fast Josephus survivor.
     * Returns 0-indexed position of the final survivor.
     */
    static long josephus(long n, long k) {
        if (n == 1) {
            return 0;
        }

        if (k == 1) {
            return n - 1;
        }

        if (k > n) {
            return (josephus(n - 1, k) + k) % n;
        }

        long cnt = n / k;

        long res = josephus(n - cnt, k);

        res -= n % k;

        if (res < 0) {
            res += n;
        } else {
            res += res / (k - 1);
        }

        return res;
    }
}
