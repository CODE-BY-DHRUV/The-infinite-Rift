import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder output = new StringBuilder();

        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            String s = st.nextToken();
            int k = Integer.parseInt(st.nextToken());

            int n = s.length();

            boolean[] inS = new boolean[26];

            for (char c : s.toCharArray()) {
                inS[c - 'a'] = true;
            }

            // Minimum possible overlap.
            int availableNotInS = 26 - n;

            // If we cannot select n characters with at most k
            // characters from s, it is impossible.
            if (availableNotInS + k < n) {
                output.append("NOPE\n");
                continue;
            }

            StringBuilder ans = new StringBuilder();

            int common = 0;
            int remaining = n;

            for (int i = 0; i < 26 && remaining > 0; i++) {

                // If we take this character:
                int newCommon = common + (inS[i] ? 1 : 0);

                // Number of characters still available after taking it.
                int availableAfter = 25 - i;

                // We need to choose 'remaining - 1' more characters.
                if (newCommon <= k && availableAfter >= remaining - 1) {
                    ans.append((char) ('a' + i));
                    common = newCommon;
                    remaining--;
                }
            }

            if (remaining > 0) {
                output.append("NOPE\n");
            } else {
                output.append(ans).append('\n');
            }
        }

        System.out.print(output);
    }
}

