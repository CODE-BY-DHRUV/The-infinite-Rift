
import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );
        StringTokenizer st;

        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner();
        StringBuilder sb = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {

            int f = fs.nextInt();
            int h = fs.nextInt();
            int w = fs.nextInt();

            int[] p = new int[f];

            for (int i = 0; i < f; i++) {
                p[i] = fs.nextInt();
            }

            Arrays.sort(p);

            int minWidth = p[0];

            for (int i = 1; i < f; i++) {
                minWidth = Math.min(minWidth, p[i] - p[i - 1]);
            }

            minWidth = Math.min(minWidth, w - p[f - 1]);

            int answer = h * minWidth;

            sb.append(answer).append('\n');
        }

        System.out.print(sb);
    }
}
