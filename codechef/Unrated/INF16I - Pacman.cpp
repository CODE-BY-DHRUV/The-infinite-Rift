
import java.io.*;
import java.util.*;

public class Main {
    static int N, K;
    static int[] dep, copies, special;
    static int[] depth;

    static int getDepth(int u) {
        if (depth[u] != -1) return depth[u];

        if (dep[u] == -1) {
            return depth[u] = 1;
        }

        return depth[u] = 1 + getDepth(dep[u]);
    }

    static boolean canInstall(int u, int[] remaining) {
        int cur = u;

        while (cur != -1) {
            if (remaining[cur] == 0) return false;
            cur = dep[cur];
        }

        return true;
    }

    static void install(int u, int[] remaining) {
        int cur = u;

        while (cur != -1) {
            remaining[cur]--;
            cur = dep[cur];
        }
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            K = Integer.parseInt(st.nextToken());

            dep = new int[N];
            for (int i = 0; i < N; i++) dep[i] = -1;

            for (int i = 0; i < N; i++) {
                st = new StringTokenizer(br.readLine());
                int x = Integer.parseInt(st.nextToken()) - 1;
                int y = Integer.parseInt(st.nextToken());
                dep[x] = (y == -1 ? -1 : y - 1);
            }

            copies = new int[N];
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) {
                copies[i] = Integer.parseInt(st.nextToken());
            }

            special = new int[K];
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < K; i++) {
                special[i] = Integer.parseInt(st.nextToken()) - 1;
            }

            depth = new int[N];
            Arrays.fill(depth, -1);

            Integer[] order = new Integer[K];
            for (int i = 0; i < K; i++) order[i] = special[i];

            Arrays.sort(order, (a, b) -> Integer.compare(
                getDepth(a), getDepth(b)));

            int[] remaining = copies.clone();
            int answer = 0;

            for (int u : order) {
                if (canInstall(u, remaining)) {
                    install(u, remaining);
                    answer++;
                }
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}
