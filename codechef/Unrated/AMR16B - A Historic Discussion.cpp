import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine();
        if (line == null) return;
        
        int T = Integer.parseInt(line.trim());
        StringBuilder sb = new StringBuilder();

        while (T-- > 0) {
            int N = Integer.parseInt(br.readLine().trim());
            
            // Find minimum K such that 2^K >= N
            int K = 0;
            while ((1 << K) < N) {
                K++;
            }
            sb.append(K).append("\n");

            // Matrix to store the binary vector of length K for each person (1-indexed)
            int[][] mat = new int[N + 1][K];
            
            // Assign binary representation to the first N/2 people
            for (int i = 1; i <= N / 2; i++) {
                int val = i - 1;
                for (int j = 0; j < K; j++) {
                    mat[i][j] = (val >> j) & 1;
                }
            }
            
            // Assign bitwise negation to the remaining N/2 people
            for (int i = 1; i <= N / 2; i++) {
                int target = N / 2 + i;
                for (int j = 0; j < K; j++) {
                    mat[target][j] = 1 - mat[i][j];
                }
            }

            // For each discussion (column), output Group 0 followed by Group 1
            for (int j = 0; j < K; j++) {
                StringBuilder group0 = new StringBuilder();
                StringBuilder group1 = new StringBuilder();
                
                for (int i = 1; i <= N; i++) {
                    if (mat[i][j] == 0) {
                        group0.append(i).append(" ");
                    } else {
                        group1.append(i).append(" ");
                    }
                }
                sb.append(group0).append(group1.toString().trim()).append("\n");
            }
        }
        System.out.print(sb);
    }
}