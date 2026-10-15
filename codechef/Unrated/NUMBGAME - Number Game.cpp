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

        String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }
            return sb.toString();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    static int solve(String a, int m) {
        int n = a.length();

        if (m == 1) return n;

        int[] pow10 = new int[n + 1];
        int[] prefix = new int[n + 1];
        int[] suffix = new int[n + 1];
        int[] rem = new int[n];

        pow10[0] = 1 % m;
        for (int i = 1; i <= n; i++) {
            pow10[i] = (int) ((long) pow10[i - 1] * 10 % m);
        }

        for (int i = 0; i < n; i++) {
            int d = a.charAt(i) - '0';
            prefix[i + 1] = (int) (((long) prefix[i] * 10 + d) % m);
        }

        for (int i = n - 1; i >= 0; i--) {
            int d = a.charAt(i) - '0';
            suffix[i] = (int) (((long) d * pow10[n - 1 - i]
                    + suffix[i + 1]) % m);
        }

        boolean[] available = new boolean[m];

        for (int i = 0; i < n; i++) {
            int len = n - i - 1;
            rem[i] = (int) (((long) prefix[i] * pow10[len]
                    + suffix[i + 1]) % m);
            available[rem[i]] = true;
        }

        int chunkPower = pow10[n - 1];
        int count = 0;

        for (boolean b : available) {
            if (b) count++;
        }

        int[] chunks = new int[count];
        int k = 0;
        for (int r = 0; r < m; r++) {
            if (available[r]) chunks[k++] = r;
        }

        // Reverse graph: find every remainder that can eventually reach 0.
        int[] head = new int[m];
        Arrays.fill(head, -1);

        int edges = m * count;
        int[] to = new int[edges];
        int[] next = new int[edges];
        int e = 0;

        for (int r = 0; r < m; r++) {
            for (int c : chunks) {
                int nr = (int) (((long) r * chunkPower + c) % m);
                to[e] = r;
                next[e] = head[nr];
                head[nr] = e++;
            }
        }

        boolean[] good = new boolean[m];
        int[] queue = new int[m];
        int front = 0, back = 0;

        good[0] = true;
        queue[back++] = 0;

        while (front < back) {
            int cur = queue[front++];

            for (int edge = head[cur]; edge != -1; edge = next[edge]) {
                int prev = to[edge];

                if (!good[prev]) {
                    good[prev] = true;
                    queue[back++] = prev;
                }
            }
        }

        int answer = 0;
        for (int r : rem) {
            if (good[r]) answer++;
        }

        return answer;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        int t = fs.nextInt();
        StringBuilder out = new StringBuilder();

        while (t-- > 0) {
            String a = fs.next();
            int m = fs.nextInt();
            out.append(solve(a, m)).append('\n');
        }

        System.out.print(out);
    }
}