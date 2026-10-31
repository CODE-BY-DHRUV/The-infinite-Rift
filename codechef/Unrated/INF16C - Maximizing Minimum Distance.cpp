
import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());

        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {

            int n = Integer.parseInt(br.readLine().trim());

            int m = n + 1;

            double scale = Math.sqrt((double) m / n);
            double h = 1.0 / Math.sqrt(m);

            // Householder vector
            double[] u = new double[m];

            for (int i = 0; i < m; i++) {
                u[i] = h;
            }

            u[m - 1] += 1.0;

            double normSq = 0;

            for (int i = 0; i < m; i++) {
                normSq += u[i] * u[i];
            }

            // Generate N+1 points, each having N coordinates
            for (int i = 0; i < m; i++) {

                for (int j = 0; j < n; j++) {

                    // Householder matrix:
                    // H = I - 2 * u * u^T / |u|^2

                    double value = (i == j ? 1.0 : 0.0)
                            - 2.0 * u[i] * u[j] / normSq;

                    // Projection and normalization
                    value *= scale;

                    if (j > 0) {
                        sb.append(' ');
                    }

                    sb.append(String.format(
                        java.util.Locale.US, "%.10f", value
                    ));
                }

                sb.append('\n');
            }

            if (t > 0) {
                sb.append('\n');
            }
        }

        System.out.print(sb);
    }
}

