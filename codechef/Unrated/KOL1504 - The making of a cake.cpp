
import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());

        while (t-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            int n = Integer.parseInt(st.nextToken());
            int d = Integer.parseInt(st.nextToken());

            String a = br.readLine().trim();
            String b = br.readLine().trim();

            boolean possible = true;

            for (int r = 0; r < d && r < n; r++) {

                int[] freq = new int[26];

                for (int i = r; i < n; i += d) {
                    freq[a.charAt(i) - 'a']++;
                    freq[b.charAt(i) - 'a']--;
                }

                for (int count : freq) {
                    if (count != 0) {
                        possible = false;
                        break;
                    }
                }

                if (!possible) {
                    break;
                }
            }

            System.out.println(possible ? "Yes" : "No");
        }
    }
}
