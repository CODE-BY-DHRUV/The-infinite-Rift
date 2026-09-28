import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());

            long[] a = new long[n];

            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 0; i < n; i++) {
                a[i] = Long.parseLong(st.nextToken());
            }

            Arrays.sort(a);

            long ans = 0;

            for (int i = 0; i < n / 2; i++) {
                ans -= a[i];
            }

            for (int i = n / 2; i < n; i++) {
                ans += a[i];
            }

            System.out.println(ans);
        }
    }
}