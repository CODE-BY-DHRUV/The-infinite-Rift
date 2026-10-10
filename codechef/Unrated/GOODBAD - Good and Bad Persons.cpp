
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
            StringTokenizer st =
                new StringTokenizer(br.readLine());

            int N = Integer.parseInt(st.nextToken());
            int K = Integer.parseInt(st.nextToken());

            String s = br.readLine().trim();

            int upper = 0;
            int lower = 0;

            for (int i = 0; i < N; i++) {
                char c = s.charAt(i);

                if (Character.isUpperCase(c)) {
                    upper++;
                } else {
                    lower++;
                }
            }

            boolean chef = upper <= K;
            boolean brother = lower <= K;

            if (chef && brother) {
                out.append("both\n");
            } else if (chef) {
                out.append("chef\n");
            } else if (brother) {
                out.append("brother\n");
            } else {
                out.append("none\n");
            }
        }

        System.out.print(out);
    }
}

