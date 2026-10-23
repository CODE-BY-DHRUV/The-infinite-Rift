import java.io.*;
import java.util.Arrays;

public class Main {

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

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);

            int value = 0;
            while (c > ' ') {
                value = value * 10 + c - '0';
                c = read();
            }
            return value;
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder output = new StringBuilder();

        int T = fs.nextInt();

        while (T-- > 0) {
            int N = fs.nextInt();
            int K = fs.nextInt();

            // Read the manager of every employee.
            int[] parent = new int[N + 1];
            parent[1] = 0;

            for (int i = 2; i <= N; i++) {
                parent[i] = fs.nextInt();
            }

            // Compute depths using parent pointers.
            int[] depth = new int[N + 1];
            Arrays.fill(depth, -1);
            depth[1] = 0;

            int[] path = new int[N];

            for (int i = 2; i <= N; i++) {
                if (depth[i] != -1) continue;

                int len = 0;
                int cur = i;

                while (depth[cur] == -1) {
                    path[len++] = cur;
                    cur = parent[cur];
                }

                while (len > 0) {
                    int node = path[--len];
                    depth[node] = depth[parent[node]] + 1;
                }
            }

            // Store all client lists in one flat array.
            // Total client entries are at most 1,000,000.
            int[] clients = new int[1_000_000];
            int[] offset = new int[K + 1];
            int[] topClient = new int[K];

            int total = 0;

            for (int i = 0; i < K; i++) {
                offset[i] = total;

                int s = fs.nextInt();
                int shallowest = -1;

                for (int j = 0; j < s; j++) {
                    int employee = fs.nextInt();
                    clients[total++] = employee;

                    if (shallowest == -1 ||
                        depth[employee] < depth[shallowest]) {
                        shallowest = employee;
                    }
                }

                topClient[i] = shallowest;
            }
            offset[K] = total;

            // Bucket traders by the depth of their
            // shallowest client, using linked lists.
            int[] head = new int[N + 1];
            Arrays.fill(head, -1);

            int[] nextTrader = new int[K];

            for (int i = 0; i < K; i++) {
                int d = depth[topClient[i]];
                nextTrader[i] = head[d];
                head[d] = i;
            }

            // Greedy: process deepest topmost client first.
            boolean[] arrested = new boolean[N + 1];
            int answer = 0;

            for (int d = N; d >= 0; d--) {
                for (int trader = head[d];
                     trader != -1;
                     trader = nextTrader[trader]) {

                    boolean covered = false;

                    for (int j = offset[trader];
                         j < offset[trader + 1]; j++) {

                        if (arrested[clients[j]]) {
                            covered = true;
                            break;
                        }
                    }

                    if (!covered) {
                        // Arrest the shallowest client.
                        arrested[topClient[trader]] = true;
                        answer++;
                    }
                }
            }

            output.append(answer).append('\n');
        }

        System.out.print(output);
    }
}