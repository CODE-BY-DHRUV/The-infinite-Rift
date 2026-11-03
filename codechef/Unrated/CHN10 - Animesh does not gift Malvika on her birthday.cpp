import java.io.*;
import java.util.*;

public class Main {

    static final long MOD = 1_000_000_007L;

    static long[] fact = new long[51];

    static void precompute() {
        fact[0] = 1;

        for (int i = 1; i <= 50; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }
    }

    static long modPow(long a, long b) {
        long res = 1;

        while (b > 0) {
            if ((b & 1) == 1) {
                res = res * a % MOD;
            }

            a = a * a % MOD;
            b >>= 1;
        }

        return res;
    }

    static long inverse(long x) {
        return modPow(x, MOD - 2);
    }

    static long countAutomorphisms(
            int n, boolean[][] adj) {

        boolean[] visited = new boolean[n];

        HashMap<String, Integer> count =
                new HashMap<>();

        long ans = 1;

        for (int i = 0; i < n; i++) {

            if (visited[i]) continue;

            ArrayList<Integer> component =
                    new ArrayList<>();

            Queue<Integer> q = new LinkedList<>();

            q.add(i);
            visited[i] = true;

            while (!q.isEmpty()) {

                int u = q.poll();
                component.add(u);

                for (int v = 0; v < n; v++) {

                    // Complement graph
                    if (u != v && !adj[u][v]
                            && !visited[v]) {

                        visited[v] = true;
                        q.add(v);
                    }
                }
            }

            int k = component.size();

            int edges = 0;

            for (int u : component) {
                for (int v : component) {
                    if (u < v && !adj[u][v]) {
                        edges++;
                    }
                }
            }

            long ways;

            if (k == 1) {
                ways = 1;
            }
            else if (edges == k - 1) {
                // Path
                ways = 2;
            }
            else {
                // Cycle
                ways = 2L * k;
            }

            ans = ans * ways % MOD;

            // Group identical components
            String key = getKey(k, edges);

            count.put(key,
                    count.getOrDefault(key, 0) + 1);
        }

        for (int c : count.values()) {
            ans = ans * fact[c] % MOD;
        }

        return ans;
    }

    static String getKey(int k, int edges) {

        if (k == 1) return "I";

        if (edges == k - 1) {
            return "P" + k;
        }

        return "C" + k;
    }

    public static void main(String[] args)
            throws IOException {

        FastScanner fs = new FastScanner(System.in);

        StringBuilder out = new StringBuilder();

        precompute();

        int t = fs.nextInt();

        while (t-- > 0) {

            int n = fs.nextInt();

            boolean[][] adj = new boolean[n][n];

            for (int i = 0; i < n; i++) {

                String s = fs.next();

                for (int j = 0; j < n; j++) {
                    adj[i][j] = s.charAt(j) == '1';
                }
            }

            long automorphisms =
                    countAutomorphisms(n, adj);

            long numerator = fact[n];

            long answer =
                    numerator * inverse(automorphisms) % MOD;

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {

        BufferedReader br;
        StringTokenizer st;

        FastScanner(InputStream in) {
            br = new BufferedReader(
                    new InputStreamReader(in));
        }

        String next() throws IOException {

            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }

            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
}