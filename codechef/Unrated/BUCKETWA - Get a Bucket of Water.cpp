import java.io.*;
import java.util.*;

public class Main {

    static double dH, dL, dR, k;

    // Time taken, ignoring the common walking speed
    static double time(double x) {
        double empty = Math.sqrt(dH * dH + x * x);
        double filled = Math.sqrt(dL * dL + (dR - x) * (dR - x));

        return empty + k * filled;
    }

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        StringBuilder out = new StringBuilder();

        while (sc.hasNextDouble()) {
            dH = sc.nextDouble();
            dL = sc.nextDouble();
            dR = sc.nextDouble();
            k = sc.nextDouble();

            if (dH == 0 && dL == 0 && dR == 0 && k == 0) {
                break;
            }

            /*
             * The optimal point must lie between the perpendicular
             * projections of H and L on the river.
             *
             * So search x in [0, dR].
             */
            double lo = 0.0;
            double hi = dR;

            // Sufficiently many iterations for 1e-2 accuracy
            for (int i = 0; i < 200; i++) {
                double m1 = lo + (hi - lo) / 3.0;
                double m2 = hi - (hi - lo) / 3.0;

                if (time(m1) < time(m2)) {
                    hi = m2;
                } else {
                    lo = m1;
                }
            }

            double x = (lo + hi) / 2.0;

            double empty = Math.sqrt(dH * dH + x * x);
            double filled = Math.sqrt(
                    dL * dL + (dR - x) * (dR - x)
            );

            double answer = empty + filled;

            out.append(String.format(Locale.US, "%.2f%n", answer));
        }

        System.out.print(out);
    }
}
