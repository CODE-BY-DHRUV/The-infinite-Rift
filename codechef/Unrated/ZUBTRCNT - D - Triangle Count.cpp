
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        for (int tc = 1; tc <= T; tc++) {
            long L = sc.nextLong();
            long K = sc.nextLong();

            long ans = 0;

            if (K <= L) {
                long n = L - K + 1;
                ans = n * (n + 1) / 2;
            }

            System.out.println("Case " + tc + ": " + ans);
        }

        sc.close();
    }
}
