
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int E = Integer.parseInt(st.nextToken());

            int[] x = new int[n];
            st = new StringTokenizer(br.readLine());

            int min = Integer.MAX_VALUE;
            int max = Integer.MIN_VALUE;
            int minIdx = -1, maxIdx = -1, exactIdx = -1;

            for (int i = 0; i < n; i++) {
                x[i] = Integer.parseInt(st.nextToken());

                if (x[i] < min) {
                    min = x[i];
                    minIdx = i;
                }
                if (x[i] > max) {
                    max = x[i];
                    maxIdx = i;
                }
                if (x[i] == E && exactIdx == -1) {
                    exactIdx = i;
                }
            }

            if (E < min || E > max) {
                out.append("-1\n");
                continue;
            }

            double[] p = new double[n];

            if (exactIdx != -1) {
                p[exactIdx] = 1.0;
            } else {
                double low = x[minIdx];
                double high = x[maxIdx];

                p[minIdx] = (high - E) / (high - low);
                p[maxIdx] = (E - low) / (high - low);
            }

            for (int i = 0; i < n; i++) {
                if (i > 0) out.append(' ');
                out.append(String.format(Locale.US, "%.10f", p[i]));
            }
            out.append('\n');
        }

        System.out.print(out);
    }
}
