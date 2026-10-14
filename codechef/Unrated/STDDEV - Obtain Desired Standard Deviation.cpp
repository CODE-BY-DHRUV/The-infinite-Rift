import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        while (t-- > 0) {
            int n = sc.nextInt();
            double sigma = sc.nextDouble();

            if (n == 1) {
                if (sigma == 0) {
                    System.out.println("0");
                } else {
                    System.out.println("-1");
                }
                continue;
            }

            double v = n * sigma / Math.sqrt(n - 1.0);

            if (v > 1e8) {
                System.out.println("-1");
                continue;
            }

            for (int i = 0; i < n - 1; i++) {
                System.out.print("0 ");
            }
            System.out.printf(Locale.US, "%.10f%n", v);
        }

        sc.close();
    }
}