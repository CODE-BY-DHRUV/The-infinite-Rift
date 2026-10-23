import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        
        String line = br.readLine();
        if (line == null || line.trim().isEmpty()) return;
        int T = Integer.parseInt(line.trim());
        
        StringBuilder out = new StringBuilder();
        
        while (T-- > 0) {
            line = br.readLine();
            while (line != null && line.trim().isEmpty()) {
                line = br.readLine();
            }
            if (line == null) break;
            int N = Integer.parseInt(line.trim());
            
            st = new StringTokenizer(br.readLine());
            HashSet<Integer> uniqueIDs = new HashSet<>();
            for (int i = 0; i < N; i++) {
                uniqueIDs.add(Integer.parseInt(st.nextToken()));
            }
            
            // Total fake votes = Total votes (N) - Unique valid voters
            int fakeVotes = N - uniqueIDs.size();
            out.append(fakeVotes).append("\n");
        }
        
        System.out.print(out);
    }
}