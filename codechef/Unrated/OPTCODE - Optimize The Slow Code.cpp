import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {
            int N = Integer.parseInt(br.readLine().trim());

            // For each X, store the maximum Y
            HashMap<Integer, Integer> map = new HashMap<>();

            for (int i = 0; i < N; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());

                int x = Integer.parseInt(st.nextToken());
                int y = Integer.parseInt(st.nextToken());

                map.put(x, Math.max(map.getOrDefault(x, 0), y));
            }

            // Need at least 3 distinct X values
            if (map.size() < 3) {
                System.out.println(0);
                continue;
            }

            // Find the three largest Y values
            long first = 0;
            long second = 0;
            long third = 0;

            for (int y : map.values()) {
                if (y >= first) {
                    third = second;
                    second = first;
                    first = y;
                } else if (y >= second) {
                    third = second;
                    second = y;
                } else if (y > third) {
                    third = y;
                }
            }

            System.out.println(first + second + third);
        }
    }
}