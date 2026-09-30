import java.io.*;

public class Main {

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(
                new InputStreamReader(System.in)
        );

        long N = Long.parseLong(br.readLine().trim());

        double expected = 0.0;

        /*
         * We need E[v] for v = 2N-1 down to N.
         *
         * For each v:
         * m = ceil(log2(v + 1))
         *
         * This can be obtained as:
         * m = bitLength(v)
         *
         * because:
         * v = 3 -> m = 2
         * v = 4 -> m = 3
         * v = 7 -> m = 3
         * v = 8 -> m = 4
         */
        for (long v = 2 * N - 1; v >= N; v--) {

            int m = 64 - Long.numberOfLeadingZeros(v);

            double failureProbability = Math.scalb(1.0, -m);
            double p = 1.0 - failureProbability;

            expected = p * (2.0 + expected);
        }

        System.out.printf("%.12f%n", expected);
    }
}