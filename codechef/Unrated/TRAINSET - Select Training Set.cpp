import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {

            int N = Integer.parseInt(br.readLine().trim());

            // word -> [count of 0, count of 1]
            HashMap<String, int[]> map = new HashMap<>();

            for (int i = 0; i < N; i++) {

                StringTokenizer st = new StringTokenizer(br.readLine());

                String word = st.nextToken();
                int type = Integer.parseInt(st.nextToken());

                int[] count = map.get(word);

                if (count == null) {
                    count = new int[2];
                    map.put(word, count);
                }

                count[type]++;
            }

            int answer = 0;

            for (int[] count : map.values()) {
                answer += Math.max(count[0], count[1]);
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}