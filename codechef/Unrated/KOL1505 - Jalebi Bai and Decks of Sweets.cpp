
import java.io.*;
import java.util.*;

public class Main {

    static String compress(String s) {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < s.length(); i++) {
            if (i == 0 || s.charAt(i) != s.charAt(i - 1)) {
                sb.append(s.charAt(i));
            }
        }

        return sb.toString();
    }

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());

        StringBuilder ans = new StringBuilder();

        while (T-- > 0) {

            String s = br.readLine().trim();
            String t = br.readLine().trim();

            if (compress(s).equals(compress(t))) {
                ans.append("Yes\n");
            } else {
                ans.append("No\n");
            }
        }

        System.out.print(ans);
    }
}
