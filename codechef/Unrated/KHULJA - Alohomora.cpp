import java.io.*;
import java.util.*;

public class Main {

    static final double PI = Math.PI;

    // ---------------------------------------------------------
    // FFT
    // ---------------------------------------------------------
    static void fft(double[] real, double[] imag, boolean invert) {
        int n = real.length;

        // Bit reversal
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;

            while ((j & bit) != 0) {
                j ^= bit;
                bit >>= 1;
            }

            j ^= bit;

            if (i < j) {
                double tmp = real[i];
                real[i] = real[j];
                real[j] = tmp;

                tmp = imag[i];
                imag[i] = imag[j];
                imag[j] = tmp;
            }
        }

        // FFT
        for (int len = 2; len <= n; len <<= 1) {

            double angle = 2 * PI / len * (invert ? -1 : 1);

            double wLenReal = Math.cos(angle);
            double wLenImag = Math.sin(angle);

            for (int i = 0; i < n; i += len) {

                double wReal = 1;
                double wImag = 0;

                for (int j = 0; j < len / 2; j++) {

                    int u = i + j;
                    int v = i + j + len / 2;

                    double vReal =
                            real[v] * wReal - imag[v] * wImag;

                    double vImag =
                            real[v] * wImag + imag[v] * wReal;

                    real[v] = real[u] - vReal;
                    imag[v] = imag[u] - vImag;

                    real[u] += vReal;
                    imag[u] += vImag;

                    double nextReal =
                            wReal * wLenReal - wImag * wLenImag;

                    double nextImag =
                            wReal * wLenImag + wImag * wLenReal;

                    wReal = nextReal;
                    wImag = nextImag;
                }
            }
        }

        if (invert) {
            for (int i = 0; i < n; i++) {
                real[i] /= n;
                imag[i] /= n;
            }
        }
    }

    // ---------------------------------------------------------
    // Convolution
    // ---------------------------------------------------------
    static long[] convolution(long[] a, long[] b) {

        int required = a.length + b.length - 1;

        int size = 1;
        while (size < required) {
            size <<= 1;
        }

        double[] ar = new double[size];
        double[] ai = new double[size];

        double[] br = new double[size];
        double[] bi = new double[size];

        for (int i = 0; i < a.length; i++)
            ar[i] = a[i];

        for (int i = 0; i < b.length; i++)
            br[i] = b[i];

        fft(ar, ai, false);
        fft(br, bi, false);

        for (int i = 0; i < size; i++) {

            double real =
                    ar[i] * br[i] - ai[i] * bi[i];

            double imag =
                    ar[i] * bi[i] + ai[i] * br[i];

            ar[i] = real;
            ai[i] = imag;
        }

        fft(ar, ai, true);

        long[] result = new long[required];

        for (int i = 0; i < required; i++) {
            result[i] = Math.round(ar[i]);
        }

        return result;
    }

    // ---------------------------------------------------------
    // cost[x][d] = time to rotate x -> d
    // ---------------------------------------------------------
    static long[][] buildCost(int[] rotate) {

        long[][] cost = new long[10][10];

        for (int start = 0; start < 10; start++) {

            long current = 0;

            for (int step = 0; step < 10; step++) {

                int digit = (start + step) % 10;

                cost[start][digit] = current;

                // Rotate digit -> digit + 1
                current += rotate[digit];
            }
        }

        return cost;
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br =
                new BufferedReader(new InputStreamReader(System.in));

        StringTokenizer st =
                new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());

        String s = br.readLine().trim();
        String t = br.readLine().trim();

        int[] a = new int[10];
        int[] b = new int[10];

        st = new StringTokenizer(br.readLine());

        for (int i = 0; i < 10; i++) {
            a[i] = Integer.parseInt(st.nextToken());
        }

        st = new StringTokenizer(br.readLine());

        for (int i = 0; i < 10; i++) {
            b[i] = Integer.parseInt(st.nextToken());
        }

        /*
         * lockCost[x][d]:
         * time required to turn lock digit x into d
         */
        long[][] lockCost = buildCost(a);

        /*
         * keyCost[x][d]:
         * time required to turn key digit x into d
         */
        long[][] keyCost = buildCost(b);

        /*
         * pairCost[x][y]:
         *
         * Minimum time to make lock digit x
         * and key digit y equal.
         */
        long[][] pairCost = new long[10][10];

        for (int x = 0; x < 10; x++) {

            for (int y = 0; y < 10; y++) {

                long best = Long.MAX_VALUE;

                for (int d = 0; d < 10; d++) {

                    long value =
                            lockCost[x][d]
                            + keyCost[y][d];

                    best = Math.min(best, value);
                }

                pairCost[x][y] = best;
            }
        }

        /*
         * answer[index] will contain the total cost
         * for a particular alignment.
         *
         * If key starts at position 'start',
         * its convolution index is:
         *
         * start + m - 1
         */
        long[] answer = new long[n + m - 1];

        /*
         * Process one key digit at a time.
         */
        for (int y = 0; y < 10; y++) {

            long[] A = new long[n];
            long[] B = new long[m];

            /*
             * A[i] = cost of matching s[i]
             *        with key digit y.
             */
            for (int i = 0; i < n; i++) {

                int x = s.charAt(i) - '0';

                A[i] = pairCost[x][y];
            }

            /*
             * Reverse t.
             *
             * B[j] = 1 if reversed key position
             *        contains digit y.
             */
            for (int j = 0; j < m; j++) {

                int digit =
                        t.charAt(m - 1 - j) - '0';

                if (digit == y)
                    B[j] = 1;
            }

            long[] conv = convolution(A, B);

            /*
             * Add this digit's contribution.
             */
            for (int i = 0; i < conv.length; i++) {
                answer[i] += conv[i];
            }
        }

        long result = Long.MAX_VALUE;

        /*
         * Valid starting positions are:
         *
         * 0 ... n-m
         */
        for (int start = 0; start <= n - m; start++) {

            int index = start + m - 1;

            result = Math.min(
                    result,
                    answer[index]
            );
        }

        System.out.println(result);
    }
}