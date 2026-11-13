import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line;
        
        while ((line = br.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) continue;
            if (line.equals("End")) break;

            int n = line.length();
            int[] pi = new int[n];
            
            // Compute KMP prefix function (pi array)
            for (int i = 1; i < n; i++) {
                int j = pi[i - 1];
                while (j > 0 && line.charAt(i) != line.charAt(j)) {
                    j = pi[j - 1];
                }
                if (line.charAt(i) == line.charAt(j)) {
                    j++;
                }
                pi[i] = j;
            }

            // Build output string without trailing spaces
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < n; i++) {
                if (i > 0) {
                    sb.append(' ');
                }
                sb.append(pi[i]);
            }
            System.out.println(sb.toString());
        }
    }
}
