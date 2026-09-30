import java.io.*;
import java.util.*;

public class Main {

    static long gcd(long a, long b) {
        while (b != 0) {
            long temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    // Returns LCM, but stops at limit if LCM > limit
    static long lcm(long a, long b, long limit) {
        long g = gcd(a, b);

        // a / gcd(a,b) * b
        long x = a / g;

        if (x > limit / b) {
            return limit + 1;
        }

        return x * b;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        while (T-- > 0) {
            int N = sc.nextInt();

            long[] rebels = new long[N];

            for (int i = 0; i < N; i++) {
                rebels[i] = sc.nextLong();
            }

            long lower = sc.nextLong();
            long upper = sc.nextLong();

            long L = 1;

            for (int i = 0; i < N; i++) {
                L = lcm(L, rebels[i], upper);

                // L > upper means no King's soldier
                // can be a multiple of L.
                if (L > upper) {
                    break;
                }
            }

            long defeated = 0;

            if (L <= upper) {
                defeated = upper / L - (lower - 1) / L;
            }

            long total = upper - lower + 1;
            long survivors = total - defeated;

            System.out.println(survivors);
        }

        sc.close();
    }
}
