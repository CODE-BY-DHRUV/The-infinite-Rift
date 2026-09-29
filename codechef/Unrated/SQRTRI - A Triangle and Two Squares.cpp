import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        while (T-- > 0) {
            long a = sc.nextLong();
            long b = sc.nextLong();
            long x = sc.nextLong();
            long y = sc.nextLong();

            long available = a - b;

            boolean possible =
                    a * b <= (a - x) * available ||
                    a * b <= (x + b) * available ||
                    a * b <= (a - y) * available ||
                    a * b <= (y + b) * available;

            System.out.println(possible ? "yes" : "no");
        }

        sc.close();
    }
}