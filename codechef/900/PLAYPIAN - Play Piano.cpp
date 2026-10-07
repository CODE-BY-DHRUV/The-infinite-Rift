import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {
            String s = br.readLine().trim();

            boolean valid = true;

            for (int i = 0; i < s.length(); i += 2) {
                if (s.charAt(i) == s.charAt(i + 1)) {
                    valid = false;
                    break;
                }
            }

            System.out.println(valid ? "yes" : "no");
        }
    }
}
