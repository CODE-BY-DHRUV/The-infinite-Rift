import java.io.*;

public class Main {

    static int[] topValue = new int[4];
    static int[] topIndex = new int[4];

    static void addTop(int value, int index) {
        for (int i = 0; i < 4; i++) {
            if (value > topValue[i]) {
                for (int j = 3; j > i; j--) {
                    topValue[j] = topValue[j - 1];
                    topIndex[j] = topIndex[j - 1];
                }
                topValue[i] = value;
                topIndex[i] = index;
                return;
            }
        }
    }

    static int maxExcluding(int a, int b, int c) {
        for (int i = 0; i < 4; i++) {
            if (topIndex[i] != -1 &&
                topIndex[i] != a &&
                topIndex[i] != b &&
                topIndex[i] != c) {
                return topValue[i];
            }
        }
        return 0;
    }

    static int solve(String s) {
        int n = s.length();

        if (n == 1) return 1;

        boolean allSame = true;
        for (int i = 1; i < n; i++) {
            if (s.charAt(i) != s.charAt(0)) {
                allSame = false;
                break;
            }
        }

        if (allSame) return n - 1;

        // Start at a circular boundary.
        int start = 0;
        while (s.charAt(start) == s.charAt((start + n - 1) % n)) {
            start++;
        }

        // Extract circular runs.
        int[] runs = new int[n];
        int k = 0;
        int length = 1;

        for (int i = 1; i < n; i++) {
            char prev = s.charAt((start + i - 1) % n);
            char curr = s.charAt((start + i) % n);

            if (prev == curr) {
                length++;
            } else {
                runs[k++] = length;
                length = 1;
            }
        }
        runs[k++] = length;

        // Find the four largest runs, retaining their indices.
        for (int i = 0; i < 4; i++) {
            topValue[i] = -1;
            topIndex[i] = -1;
        }

        for (int i = 0; i < k; i++) {
            addTop(runs[i], i);
        }

        int answer = n;

        for (int i = 0; i < k; i++) {
            int len = runs[i];
            int prev = (i - 1 + k) % k;
            int next = (i + 1) % k;

            // Flip an endpoint of a run of length >= 2.
            if (len >= 2) {
                int unaffected = maxExcluding(i, prev, -1);

                int candidate = Math.max(
                    unaffected,
                    Math.max(len - 1, runs[prev] + 1)
                );
                answer = Math.min(answer, candidate);

                unaffected = maxExcluding(i, next, -1);

                candidate = Math.max(
                    unaffected,
                    Math.max(len - 1, runs[next] + 1)
                );
                answer = Math.min(answer, candidate);
            }

            // Flip an interior stone to split a run.
            if (len >= 3) {
                int unaffected = maxExcluding(i, -1, -1);
                int splitMaximum = len / 2;

                int candidate = Math.max(unaffected, splitMaximum);
                answer = Math.min(answer, candidate);
            }

            // Flip a single-stone run, merging its neighbors.
            if (len == 1 && k > 2) {
                int merged = runs[prev] + 1 + runs[next];
                int unaffected = maxExcluding(i, prev, next);

                int candidate = Math.max(merged, unaffected);
                answer = Math.min(answer, candidate);
            }
        }

        return answer;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        for (int tc = 1; tc <= T; tc++) {
            String s = br.readLine().trim();

            out.append("Case ")
               .append(tc)
               .append(": ")
               .append(solve(s))
               .append('\n');
        }

        System.out.print(out);
    }
}
