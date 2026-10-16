
import java.io.*;
import java.util.*;

public class Main {
    static int[] parent, size;
    static long[] xorToParent;

    static int find(int x) {
        if (parent[x] == x) {
            return x;
        }

        int p = parent[x];
        parent[x] = find(p);
        xorToParent[x] ^= xorToParent[p];

        return parent[x];
    }

    // Returns the XOR from x to its component's root.
    static long getXor(int x) {
        find(x);
        return xorToParent[x];
    }

    static boolean addConstraint(int u, int v, long r) {
        int ru = find(u);
        int rv = find(v);

        long xu = xorToParent[u];
        long xv = xorToParent[v];

        if (ru == rv) {
            return (xu ^ xv) == r;
        }

        // XOR required between the two component roots.
        long rootXor = xu ^ xv ^ r;

        if (size[ru] < size[rv]) {
            parent[ru] = rv;
            xorToParent[ru] = rootXor;
            size[rv] += size[ru];
        } else {
            parent[rv] = ru;
            xorToParent[rv] = rootXor;
            size[ru] += size[rv];
        }

        return true;
    }

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            int n = fs.nextInt();
            int q = fs.nextInt();

            // The tree structure itself does not determine edge weights.
            for (int i = 0; i < n - 1; i++) {
                fs.nextInt();
                fs.nextInt();
            }

            parent = new int[n + 1];
            size = new int[n + 1];
            xorToParent = new long[n + 1];

            for (int i = 1; i <= n; i++) {
                parent[i] = i;
                size[i] = 1;
            }

            while (q-- > 0) {
                int type = fs.nextInt();
                int u = fs.nextInt();
                int v = fs.nextInt();

                if (type == 1) {
                    long r = fs.nextLong();

                    if (addConstraint(u, v, r)) {
                        out.append("AC\n");
                    } else {
                        out.append("WA\n");
                    }
                } else {
                    int ru = find(u);
                    int rv = find(v);

                    if (ru != rv) {
                        out.append("-1\n");
                    } else {
                        out.append(xorToParent[u] ^ xorToParent[v])
                           .append('\n');
                    }
                }
            }
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
                if (len <= 0) {
                    return -1;
                }
            }
            return buffer[ptr++];
        }

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);

            long value = 0;
            boolean negative = false;

            if (c == '-') {
                negative = true;
                c = read();
            }

            while (c > ' ') {
                value = value * 10 + c - '0';
                c = read();
            }

            return negative ? -value : value;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}

