
import java.io.*;
import java.util.*;

public class Main {
    static int n;
    static long[] s, t, ps, pt;
    static long minDuration;

    static int upperBound(long[] a, long x) {
        int l = 0, r = a.length;
        while (l < r) {
            int m = (l + r) >>> 1;
            if (a[m] <= x) l = m + 1;
            else r = m;
        }
        return l;
    }

    static int lowerBound(long[] a, long x) {
        int l = 0, r = a.length;
        while (l < r) {
            int m = (l + r) >>> 1;
            if (a[m] < x) l = m + 1;
            else r = m;
        }
        return l;
    }

    static long minCost(long x) {
        long lo = s[0] - 1;
        long hi = t[n - 1];

        // Find the optimal integer starting time L.
        while (lo + 1 < hi) {
            long mid = lo + (hi - lo) / 2;

            int ending = upperBound(t, mid + x);
            int starting = n - upperBound(s, mid);

            if (ending >= starting) {
                hi = mid;
            } else {
                lo = mid;
            }
        }

        long L = hi;
        long cost = 0;

        // Meetings starting after L must be shifted left.
        int i = upperBound(s, L);
        cost += ps[n] - ps[i] - (long)(n - i) * L;

        // Meetings ending before L + x must be shifted right.
        i = lowerBound(t, L + x);
        cost += (long)i * (L + x) - pt[i];

        return cost;
    }

    static long solve(long K) {
        long lo = 0;
        long hi = minDuration + 1;

        while (lo + 1 < hi) {
            long mid = lo + (hi - lo) / 2;

            if (minCost(mid) <= K) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        return lo;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();

        n = fs.nextInt();
        s = new long[n];
        t = new long[n];
        minDuration = Long.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            s[i] = fs.nextLong();
            t[i] = fs.nextLong();
            minDuration = Math.min(minDuration, t[i] - s[i]);
        }

        Arrays.sort(s);
        Arrays.sort(t);

        ps = new long[n + 1];
        pt = new long[n + 1];

        for (int i = 0; i < n; i++) {
            ps[i + 1] = ps[i] + s[i];
            pt[i + 1] = pt[i] + t[i];
        }

        int q = fs.nextInt();
        StringBuilder ans = new StringBuilder();

        while (q-- > 0) {
            ans.append(solve(fs.nextLong())).append('\n');
        }

        System.out.print(ans);
    }

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr, len;

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

            long value = 0;
            while (c > ' ') {
                value = value * 10 + c - '0';
                c = read();
            }
            return value;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}
