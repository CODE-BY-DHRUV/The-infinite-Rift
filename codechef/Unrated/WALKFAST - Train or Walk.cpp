
import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {

            StringTokenizer st = new StringTokenizer(br.readLine());

            int N = Integer.parseInt(st.nextToken());
            int A = Integer.parseInt(st.nextToken());
            int B = Integer.parseInt(st.nextToken());
            int C = Integer.parseInt(st.nextToken());
            int D = Integer.parseInt(st.nextToken());
            int P = Integer.parseInt(st.nextToken());
            int Q = Integer.parseInt(st.nextToken());
            int Y = Integer.parseInt(st.nextToken());

            int[] x = new int[N + 1];

            st = new StringTokenizer(br.readLine());
            for (int i = 1; i <= N; i++) {
                x[i] = Integer.parseInt(st.nextToken());
            }

            // Option 1: Walk directly from A to B
            long walkDirect =
                    (long) Math.abs(x[A] - x[B]) * P;

            long answer = walkDirect;

            // Option 2: Walk A -> C, take train C -> D, walk D -> B
            long walkToC =
                    (long) Math.abs(x[A] - x[C]) * P;

            // We can board only if we reach C by time Y.
            if (walkToC <= Y) {

                long waiting = Y - walkToC;

                long trainTime =
                        (long) Math.abs(x[C] - x[D]) * Q;

                long walkFromD =
                        (long) Math.abs(x[D] - x[B]) * P;

                long viaTrain =
                        walkToC
                        + waiting
                        + trainTime
                        + walkFromD;

                answer = Math.min(answer, viaTrain);
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}

