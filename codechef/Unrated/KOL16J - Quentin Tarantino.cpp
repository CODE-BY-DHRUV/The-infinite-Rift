
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();

        while (T-- > 0) {
            int n = sc.nextInt();
            boolean[] seen = new boolean[n + 1];
            int[] a = new int[n];
            boolean valid = true;
            boolean increasing = true;

            for (int i = 0; i < n; i++) {
                a[i] = sc.nextInt();

                if (a[i] < 1 || a[i] > n || seen[a[i]]) {
                    valid = false;
                } else {
                    seen[a[i]] = true;
                }

                if (a[i] != i + 1) {
                    increasing = false;
                }
            }

            System.out.println(valid && !increasing ? "yes" : "no");
        }

        sc.close();
    }
}