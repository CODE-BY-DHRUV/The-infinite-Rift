
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        while (T-- > 0) {
            int n = sc.nextInt();

            long[] coal = new long[n];
            long[] tax = new long[Math.max(0, n - 1)];
            int[] policy = new int[Math.max(0, n - 1)];

            for (int i = 0; i < n; i++) {
                coal[i] = sc.nextLong();
            }

            for (int i = 0; i < n - 1; i++) {
                tax[i] = sc.nextLong();
            }

            for (int i = 0; i < n - 1; i++) {
                policy[i] = sc.nextInt();
            }

            long totalCoal = coal[0];
            long tollCost = 0;
            long maxProfit = totalCoal;

            for (int i = 1; i < n; i++) {
                totalCoal += coal[i];

                if (policy[i - 1] == 1) {
                    tollCost += tax[i - 1];
                } else {
                    tollCost += 2L * tax[i - 1];
                }

                long profit = totalCoal - tollCost;
                maxProfit = Math.max(maxProfit, profit);
            }

            System.out.println(maxProfit);
        }

        sc.close();
    }
}
