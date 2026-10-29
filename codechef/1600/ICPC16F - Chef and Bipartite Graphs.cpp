
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            int m = Integer.parseInt(st.nextToken());
            int d = Integer.parseInt(st.nextToken());
            int D = Integer.parseInt(st.nextToken());

            if (m < n * d || m > n * D) {
                out.append("-1\n");
                continue;
            }

            boolean[][] edge = new boolean[n][n];
            int[] leftDeg = new int[n];
            int[] rightDeg = new int[n];
            int count = 0;

            // Give every vertex degree d.
            for (int j = 0; j < d; j++) {
                for (int i = 0; i < n; i++) {
                    int v = (i + j) % n;
                    edge[i][v] = true;
                    leftDeg[i]++;
                    rightDeg[v]++;
                    count++;
                }
            }

            // Add edges while respecting maximum degree D.
            for (int i = 0; i < n && count < m; i++) {
                for (int j = 0; j < n && count < m; j++) {
                    if (!edge[i][j]
                            && leftDeg[i] < D
                            && rightDeg[j] < D) {
                        edge[i][j] = true;
                        leftDeg[i]++;
                        rightDeg[j]++;
                        count++;
                    }
                }
            }

            if (count != m) {
                out.append("-1\n");
                continue;
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (edge[i][j]) {
                        out.append(i + 1).append(' ')
                           .append(j + 1).append('\n');
                    }
                }
            }
        }

        System.out.print(out);
    }
}
