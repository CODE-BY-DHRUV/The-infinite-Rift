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

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            int res = 0;
            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }
            return res * sign;
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            int n = fs.nextInt();

            // Nodes are 1 ... n+1
            int[] degree = new int[n + 2];
            int[] color = new int[n + 2];

            // Initially node 1 is isolated and therefore remote.
            color[1] = 0;
            degree[1] = 0;

            long leaf0 = 1;
            long leaf1 = 0;

            long answer = 0;

            for (int i = 1; i <= n; i++) {
                int parent = fs.nextInt();
                int node = i + 1;

                // New node gets opposite color from its parent.
                color[node] = color[parent] ^ 1;

                // If parent currently has degree 1,
                // it is currently a remote node.
                // After adding this edge, its degree becomes 2,
                // so it stops being remote.
                if (degree[parent] == 1) {
                    if (color[parent] == 0) {
                        leaf0--;
                    } else {
                        leaf1--;
                    }
                }

                // Add the new node as a leaf.
                if (color[node] == 0) {
                    leaf0++;
                } else {
                    leaf1++;
                }

                degree[parent]++;
                degree[node] = 1;

                long beauty = Math.max(leaf0, leaf1);
                answer += beauty;
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}
