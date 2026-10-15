
import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

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

            long sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            long value = 0;
            while (c > ' ') {
                value = value * 10 + c - '0';
                c = read();
            }
            return value * sign;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }

    static class ArrayData {
        long[] values;
        long[] prefix;

        ArrayData(long[] values) {
            this.values = values;
            Arrays.sort(this.values);

            int n = values.length;
            prefix = new long[n + 1];

            for (int i = 0; i < n; i++) {
                prefix[i + 1] = prefix[i] + values[i];
            }
        }
    }

    static int lowerBound(long[] arr, long x) {
        int low = 0, high = arr.length;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] < x) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return low;
    }

    static long calculate(ArrayData a, ArrayData b) {
        // Always iterate over the smaller array.
        if (a.values.length > b.values.length) {
            ArrayData temp = a;
            a = b;
            b = temp;
        }

        long answer = 0;
        long[] small = a.values;
        long[] large = b.values;
        long[] prefix = b.prefix;
        int n = large.length;

        for (long x : small) {
            int pos = lowerBound(large, x);

            long left = x * pos - prefix[pos];
            long right = (prefix[n] - prefix[pos])
                       - x * (n - pos);

            answer += left + right;
        }

        return answer;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();

        int k = fs.nextInt();
        ArrayData[] arrays = new ArrayData[k + 1];

        for (int i = 1; i <= k; i++) {
            int size = fs.nextInt();
            long[] values = new long[size];

            for (int j = 0; j < size; j++) {
                values[j] = fs.nextLong();
            }

            arrays[i] = new ArrayData(values);
        }

        int m = fs.nextInt();

        HashMap<Long, Long> cache = new HashMap<>();
        StringBuilder out = new StringBuilder();

        for (int q = 0; q < m; q++) {
            int i = fs.nextInt();
            int j = fs.nextInt();

            if (i > j) {
                int temp = i;
                i = j;
                j = temp;
            }

            long key = ((long) i << 32) | (j & 0xffffffffL);
            Long answer = cache.get(key);

            if (answer == null) {
                answer = calculate(arrays[i], arrays[j]);
                cache.put(key, answer);
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}
