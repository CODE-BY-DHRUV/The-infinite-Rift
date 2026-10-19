import java.util.Scanner;

public class Main {

    static long gcd(long a, long b) {
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLong()) {
            long d = sc.nextLong();
            long nm = sc.nextLong();
            long nh = sc.nextLong();
            long vm = sc.nextLong();
            long vh = sc.nextLong();

            if (d == 0 && nm == 0 && nh == 0
                    && vm == 0 && vh == 0) {
                break;
            }

            long p, q;

            if (vh <= vm) {
                // Walking is at least as fast as riding.
                p = d;
                q = vm;
            } else if (nh >= nm) {
                // Every man can ride a horse directly.
                p = d;
                q = vh;
            } else {
                // Fewer horses than men: optimal horse-sharing strategy.
                p = d * (2 * nm * vh - nh * (vh - vm));
                q = vh * (2 * nm * vm + nh * (vh - vm));
            }

            long g = gcd(p, q);
            System.out.println((p / g) + "/" + (q / g));
        }

        sc.close();
    }
}