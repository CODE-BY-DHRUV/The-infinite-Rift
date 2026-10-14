import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        while (t-- > 0) {
            long n = sc.nextLong();
            long k = sc.nextLong();

            double expected = 2.0 * (1.0 + (n - 1.0) * (1.0 - 1.0 / k));

            System.out.printf(Locale.US, "%.6f%n", expected);
        }

        sc.close();
    }
}
