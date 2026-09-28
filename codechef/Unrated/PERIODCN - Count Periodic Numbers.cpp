import java.io.*;
import java.util.*;

public class Main {

    static ArrayList<Long> periodic = new ArrayList<>();

    static void generate() {
        // Binary length can be at most 30 because R <= 1e9.
        for (int len = 1; len <= 30; len++) {

            // k = length of every run
            for (int k = 1; k <= len; k++) {

                // len must be divisible by k
                if (len % k != 0) {
                    continue;
                }

                int runs = len / k;

                long num = 0;
                int bit = 1; // Binary representation always starts with 1

                for (int r = 0; r < runs; r++) {
                    for (int j = 0; j < k; j++) {
                        num = (num << 1) | bit;
                    }

                    bit ^= 1;
                }

                if (num <= 1_000_000_000L) {
                    periodic.add(num);
                }
            }
        }

        Collections.sort(periodic);
    }

    static int countPeriodic(long x) {
        if (x < 1) {
            return 0;
        }

        int low = 0;
        int high = periodic.size();

        // Upper bound: first element > x
        while (low < high) {
            int mid = (low + high) >>> 1;

            if (periodic.get(mid) <= x) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return low;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br =
                new BufferedReader(new InputStreamReader(System.in));

        generate();

        int T = Integer.parseInt(br.readLine().trim());

        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            long L = Long.parseLong(st.nextToken());
            long R = Long.parseLong(st.nextToken());

            int ans = countPeriodic(R) - countPeriodic(L - 1);

            out.append(ans).append('\n');
        }

        System.out.print(out);
    }
}