
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            int n = sc.nextInt();
            int m = sc.nextInt();

            long ans;

            if (n == 1) {
                ans = 0;
            } else if (n == 2) {
                ans = m;
            } else {
                ans = 2L * m + n - 3;
            }

            System.out.println(ans);
        }

        sc.close();
    }
}
