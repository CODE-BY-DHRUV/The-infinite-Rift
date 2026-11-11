
import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

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

    static class TrieNode {
        TrieNode[] child = new TrieNode[10];
        boolean isEnd;
    }

    static TrieNode root;

    static void insert(String word, int[] mapping) {
        TrieNode node = root;

        for (int i = 0; i < word.length(); i++) {
            int digit = mapping[word.charAt(i) - 'a'];

            if (node.child[digit] == null) {
                node.child[digit] = new TrieNode();
            }

            node = node.child[digit];
        }

        node.isEnd = true;
    }

    static int solve(int[] digits) {
        int n = digits.length;
        int INF = 1000000000;

        int[] dp = new int[n + 1];
        Arrays.fill(dp, INF);

        // Minimum words required to cover first 0 digits.
        dp[0] = 0;

        for (int i = 0; i < n; i++) {

            if (dp[i] == INF) {
                continue;
            }

            TrieNode node = root;

            // Try matching dictionary words starting at i.
            for (int j = i; j < n && j < i + 20; j++) {

                node = node.child[digits[j]];

                if (node == null) {
                    break;
                }

                if (node.isEnd) {
                    dp[j + 1] = Math.min(
                        dp[j + 1],
                        dp[i] + 1
                    );
                }
            }
        }

        return dp[n] == INF ? -1 : dp[n];
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();

        int T = fs.nextInt();

        for (int tc = 1; tc <= T; tc++) {

            int K = fs.nextInt();

            String[] words = new String[K];

            for (int i = 0; i < K; i++) {
                words[i] = fs.next();
            }

            // mapping[letter] = corresponding digit
            int[] mapping = new int[26];

            for (int i = 0; i < 10; i++) {

                int d = fs.nextInt();
                int m = fs.nextInt();

                for (int j = 0; j < m; j++) {
                    char ch = fs.next().charAt(0);
                    mapping[ch - 'a'] = d;
                }
            }

            // Build Trie using encoded dictionary words.
            root = new TrieNode();

            for (String word : words) {
                insert(word, mapping);
            }

            int n = fs.nextInt();

            int[] digits = new int[n];

            for (int i = 0; i < n; i++) {
                digits[i] = fs.nextInt();
            }

            int answer = solve(digits);

            System.out.println("Case " + tc + ": " + answer);
        }
    }
}
