
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());
            StringTokenizer st = new StringTokenizer(br.readLine());

            int ab = 0, ba = 0;
            boolean hasA = false, hasB = false;

            for (int i = 0; i < n; i++) {
                String s = st.nextToken();

                if (s.equals("ab")) {
                    ab++;
                } else if (s.equals("ba")) {
                    ba++;
                } else if (s.charAt(0) == 'a') {
                    hasA = true;
                } else {
                    hasB = true;
                }
            }

            int mixed = ab + ba;
            int chains;

            if (mixed > 0) {
                chains = Math.max(1, Math.abs(ab - ba));
            } else {
                chains = (hasA ? 1 : 0) + (hasB ? 1 : 0);
            }

            out.append(mixed + chains).append('\n');
        }

        System.out.print(out);
    }
}