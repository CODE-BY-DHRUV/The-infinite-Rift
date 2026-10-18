import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        for (int tc = 1; tc <= T; tc++) {
            int n = Integer.parseInt(br.readLine().trim());

            int[] A = new int[n];
            int[] B = new int[n];

            for (int i = 0; i < n; i++) {
                int encoded = Integer.parseInt(br.readLine().trim());

                A[i] = encoded & 65535;
                B[i] = encoded >>> 16;
            }

            out.append("Case ").append(tc).append(":\n");

            for (int i = 0; i < n; i++) {
                if (i > 0) out.append(' ');
                out.append(A[i]);
            }
            out.append('\n');

            for (int i = 0; i < n; i++) {
                if (i > 0) out.append(' ');
                out.append(B[i]);
            }
            out.append('\n');
        }

        System.out.print(out);
    }
}