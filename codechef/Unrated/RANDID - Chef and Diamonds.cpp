import java.util.*;

class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        while (T-- > 0) {
            long N = sc.nextLong();
            long Q = sc.nextLong();

            double ans = (double) Q * (N + Q + 1) / (Q + 1);

            System.out.printf("%.10f%n", ans);
        }
    }
}