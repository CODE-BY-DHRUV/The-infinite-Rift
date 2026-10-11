
import java.io.*;
import java.util.*;

public class Main {
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

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
                if (c == -1) return -1;
            } while (c <= ' ');

            int value = 0;
            while (c >= '0' && c <= '9') {
                value = value * 10 + c - '0';
                c = read();
            }
            return value;
        }
    }

    static void addEdge(
            ArrayList<Integer>[] graph,
            ArrayList<Integer>[] reverse,
            int u, int v) {
        graph[u].add(v);
        reverse[v].add(u);
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            int n = fs.nextInt();
            int m = fs.nextInt();

            int[] eu = new int[m];
            int[] ev = new int[m];

            for (int i = 0; i < m; i++) {
                eu[i] = fs.nextInt() - 1;
                ev[i] = fs.nextInt() - 1;
            }

            int pairs = n / 2;
            int nodes = 2 * pairs;

            @SuppressWarnings("unchecked")
            ArrayList<Integer>[] g = new ArrayList[nodes];
            @SuppressWarnings("unchecked")
            ArrayList<Integer>[] rg = new ArrayList[nodes];

            for (int i = 0; i < nodes; i++) {
                g[i] = new ArrayList<>();
                rg[i] = new ArrayList<>();
            }

            boolean impossible = false;

            // Literal 2*i means odd vertex is in A.
            // Literal 2*i+1 means even vertex is in A.
            // These two literals are complements.
            for (int i = 0; i < m; i++) {
                int u = eu[i], v = ev[i];

                // An unpaired vertex is always put in A.
                if (u >= nodes || v >= nodes) {
                    continue;
                }

                int lu = 2 * (u / 2) + (u % 2 == 0 ? 0 : 1);
                int lv = 2 * (v / 2) + (v % 2 == 0 ? 0 : 1);

                // Clause (u in A) OR (v in A).
                addEdge(g, rg, lu ^ 1, lv);
                addEdge(g, rg, lv ^ 1, lu);
            }

            int[] order = new int[nodes];
            boolean[] seen = new boolean[nodes];
            int[] stack = new int[nodes];
            int[] ptr = new int[nodes];
            int orderSize = 0;

            // First Kosaraju pass: iterative DFS.
            for (int s = 0; s < nodes; s++) {
                if (seen[s]) continue;

                int top = 0;
                stack[top] = s;
                ptr[top] = 0;
                top++;
                seen[s] = true;

                while (top > 0) {
                    int u = stack[top - 1];

                    if (ptr[top - 1] < g[u].size()) {
                        int v = g[u].get(ptr[top - 1]++);
                        if (!seen[v]) {
                            seen[v] = true;
                            stack[top] = v;
                            ptr[top] = 0;
                            top++;
                        }
                    } else {
                        order[orderSize++] = u;
                        top--;
                    }
                }
            }

            int[] comp = new int[nodes];
            Arrays.fill(comp, -1);
            int cid = 0;

            for (int i = orderSize - 1; i >= 0; i--) {
                int s = order[i];
                if (comp[s] != -1) continue;

                int top = 0;
                stack[top++] = s;
                comp[s] = cid;

                while (top > 0) {
                    int u = stack[--top];

                    for (int v : rg[u]) {
                        if (comp[v] == -1) {
                            comp[v] = cid;
                            stack[top++] = v;
                        }
                    }
                }
                cid++;
            }

            for (int i = 0; i < pairs; i++) {
                if (comp[2 * i] == comp[2 * i + 1]) {
                    impossible = true;
                    break;
                }
            }

            if (impossible) {
                out.append("impossible\n");
                continue;
            }

            char[] ans = new char[n];

            for (int i = 0; i < pairs; i++) {
                boolean oddInA = comp[2 * i] > comp[2 * i + 1];
                ans[2 * i] = oddInA ? '1' : '0';
                ans[2 * i + 1] = oddInA ? '0' : '1';
            }

            if (n % 2 == 1) {
                ans[n - 1] = '1';
            }

            // Final verification.
            for (int i = 0; i < m; i++) {
                if (ans[eu[i]] == '0' && ans[ev[i]] == '0') {
                    impossible = true;
                    break;
                }
            }

            if (impossible) {
                out.append("impossible\n");
            } else {
                out.append("possible\n");
                out.append(ans).append('\n');
            }
        }

        System.out.print(out);
    }
}
