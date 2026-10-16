import java.io.*;
import java.util.*;

public class Main {

    static class DSU {
        int[] parent, size;
        long[] xor;

        DSU(int n) {
            parent = new int[n + 1];
            size = new int[n + 1];
            xor = new long[n + 1];

            for (int i = 1; i <= n; i++) {
                parent[i] = i;
                size[i] = 1;
                xor[i] = 0;
            }
        }

        int find(int u) {
            if (parent[u] == u) {
                return u;
            }

            int p = parent[u];
            parent[u] = find(p);
            xor[u] ^= xor[p];

            return parent[u];
        }

        boolean addConstraint(int u, int v, long r) {
            int rootU = find(u);
            int rootV = find(v);

            if (rootU == rootV) {
                return (xor[u] ^ xor[v]) == r;
            }

            // Union by size
            if (size[rootU] < size[rootV]) {
                int temp = rootU;
                rootU = rootV;
                rootV = temp;
            }

            parent[rootV] = rootU;
            xor[rootV] = xor[u] ^ xor[v] ^ r;
            size[rootU] += size[rootV];

            return true;
        }

        long query(int u, int v) {
            int rootU = find(u);
            int rootV = find(v);

            if (rootU != rootV) {
                return -1;
            }

            return xor[u] ^ xor[v];
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        StringBuilder output = new StringBuilder();
        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {
            StringTokenizer st =
                new StringTokenizer(br.readLine());

            int n = Integer.parseInt(st.nextToken());
            int Q = Integer.parseInt(st.nextToken());

            // Read the tree edges; they are not needed afterward.
            for (int i = 0; i < n - 1; i++) {
                st = new StringTokenizer(br.readLine());
                st.nextToken();
                st.nextToken();
            }

            DSU dsu = new DSU(n);

            for (int i = 0; i < Q; i++) {
                st = new StringTokenizer(br.readLine());

                int type = Integer.parseInt(st.nextToken());
                int u = Integer.parseInt(st.nextToken());
                int v = Integer.parseInt(st.nextToken());

                if (type == 1) {
                    long r = Long.parseLong(st.nextToken());

                    if (dsu.addConstraint(u, v, r)) {
                        output.append("AC\n");
                    } else {
                        output.append("WA\n");
                    }
                } else {
                    output.append(dsu.query(u, v)).append('\n');
                }
            }
        }

        System.out.print(output);
    }
}

