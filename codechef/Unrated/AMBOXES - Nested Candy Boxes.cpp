
import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);

        int n = fs.nextInt();
        int m = fs.nextInt();

        long[] a = new long[n];
        for (int i = 0; i < n; i++) {
            a[i] = fs.nextLong();
        }

        long[] queries = new long[m];
        long maxX = 0;

        for (int i = 0; i < m; i++) {
            queries[i] = fs.nextLong();
            maxX = Math.max(maxX, queries[i]);
        }

        // Group equal prefix products together.
        long[] products = new long[n];
        int[] frequency = new int[n];
        int size = 0;

        long product = 1;

        for (int i = 0; i < n; i++) {
            if (product < maxX) {
                if (a[i] >= (maxX + product - 1) / product) {
                    product = maxX;
                } else {
                    product *= a[i];
                }
            }

            if (size > 0 && products[size - 1] == product) {
                frequency[size - 1]++;
            } else {
                products[size] = product;
                frequency[size] = 1;
                size++;
            }
        }

        // Prefix counts of the grouped products.
        long[] prefixCount = new long[size + 1];

        for (int i = 0; i < size; i++) {
            prefixCount[i + 1] = prefixCount[i] + frequency[i];
        }

        StringBuilder out = new StringBuilder();

        for (long x : queries) {
            // Find the first prefix product >= x.
            int lo = 0, hi = size;

            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                if (products[mid] < x) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }

            int idx = lo;
            long ans = n - prefixCount[idx];

            for (int i = 0; i < idx; i++) {
                long p = products[i];
                long needed = (x + p - 1) / p;
                ans += (long) frequency[i] * needed;
            }

            out.append(ans).append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        FastScanner(InputStream in) {
            this.in = in;
        }

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;

                if (len <= 0) return -1;
            }

            return buffer[ptr++];
        }

        long nextLong() throws IOException {
            int c;

            do {
                c = read();
            } while (c <= ' ' && c != -1);

            long num = 0;

            while (c > ' ') {
                num = num * 10 + c - '0';
                c = read();
            }

            return num;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}
