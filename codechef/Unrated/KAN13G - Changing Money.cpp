import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.Arrays;
import java.util.Collections;

public class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st = null;

    static String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            String line = br.readLine();
            if (line == null) return null;
            st = new StringTokenizer(line);
        }
        return st.nextToken();
    }

    public static void main(String[] args) throws IOException {
        String token = nextToken();
        if (token == null) return;
        int T = Integer.parseInt(token);

        for (int caseNum = 1; caseNum <= T; caseNum++) {
            String sN = nextToken();
            if (sN == null) break;
            int N = Integer.parseInt(sN);
            int M = Integer.parseInt(nextToken());

            Double[] dens = new Double[N];
            for (int i = 0; i < N; i++) {
                dens[i] = Double.parseDouble(nextToken());
            }

            // Sort denominations in descending order
            Arrays.sort(dens, Collections.reverseOrder());

            System.out.println("Case " + caseNum + ":");

            for (int scNum = 1; scNum <= M; scNum++) {
                double targetDouble = Double.parseDouble(nextToken());
                // Convert to cents to avoid floating-point precision errors
                long remainingCents = Math.round(targetDouble * 100.0);

                System.out.println("Scenario " + scNum + ":");

                for (int i = 0; i < N; i++) {
                    long denomCents = Math.round(dens[i] * 100.0);
                    if (remainingCents >= denomCents) {
                        long count = remainingCents / denomCents;
                        remainingCents %= denomCents;

                        // Format denomination output
                        String denomStr;
                        if (dens[i] >= 1.0) {
                            denomStr = String.valueOf(dens[i].longValue());
                        } else {
                            denomStr = String.format("%.2f", dens[i]);
                        }

                        System.out.println(denomStr + " " + count);
                    }
                }
            }
        }
    }
}