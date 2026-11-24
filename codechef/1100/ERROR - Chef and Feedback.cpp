
import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());

        StringBuilder out = new StringBuilder();

        while (t-- > 0) {
            String s = br.readLine().trim();

            boolean good = false;

            for (int i = 0; i < s.length() - 2; i++) {
                if (s.charAt(i) == s.charAt(i + 2) &&
                    s.charAt(i) != s.charAt(i + 1)) {

                    good = true;
                    break;
                }
            }

            out.append(good ? "Good" : "Bad").append('\n');
        }

        System.out.print(out);
    }
}
