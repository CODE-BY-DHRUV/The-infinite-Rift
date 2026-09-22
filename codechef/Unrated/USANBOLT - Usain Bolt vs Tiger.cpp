import java.util.*;
import java.lang.*;
import java.io.*;



public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder ans = new StringBuilder();

        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            long finish = Long.parseLong(st.nextToken());
            long distanceToBolt = Long.parseLong(st.nextToken());
            long tigerAcceleration = Long.parseLong(st.nextToken());
            long boltSpeed = Long.parseLong(st.nextToken());

            // Bolt time < Tiger time
            //
            // finish / boltSpeed
            //     <
            // sqrt(2 * (finish + distanceToBolt) / tigerAcceleration)
            //
            // Squaring and cross multiplying:
            // finish^2 * tigerAcceleration
            //     <
            // 2 * (finish + distanceToBolt) * boltSpeed^2

            long left = finish * finish * tigerAcceleration;
            long right = 2L * (finish + distanceToBolt) * boltSpeed * boltSpeed;

            if (left < right) {
                ans.append("Bolt\n");
            } else {
                ans.append("Tiger\n");
            }
        }

        System.out.print(ans);
    }
}