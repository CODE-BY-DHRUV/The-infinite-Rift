import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder output = new StringBuilder();

        while (T-- > 0) {
            int N = Integer.parseInt(br.readLine().trim());
            int[] A = new int[N];

            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) {
                A[i] = Integer.parseInt(st.nextToken());
            }

            Arrays.sort(A);

            long answer = 0;
            long prefixSum = 0;

            // Process all elements except the maximum,
            // in descending order.
            for (int i = N - 2; i >= 0; i--) {
                prefixSum += A[i];
                answer += prefixSum;
            }

            // The maximum element is always processed last.
            prefixSum += A[N - 1];
            answer += prefixSum;

            output.append(answer).append('\n');
        }

        System.out.print(output);
    }
}