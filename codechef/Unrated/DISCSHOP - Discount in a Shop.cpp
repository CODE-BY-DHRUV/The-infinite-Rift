import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {

            String s = br.readLine().trim();

            String answer = null;

            for (int i = 0; i < s.length(); i++) {

                // Remove digit at position i
                String candidate = s.substring(0, i) + s.substring(i + 1);

                // Remove leading zeros for output/comparison
                candidate = candidate.replaceFirst("^0+", "");

                // If everything was zero, answer is 0
                if (candidate.length() == 0) {
                    candidate = "0";
                }

                // Compare numbers without converting to integer
                if (answer == null ||
                    candidate.length() < answer.length() ||
                    (candidate.length() == answer.length()
                     && candidate.compareTo(answer) < 0)) {

                    answer = candidate;
                }
            }

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }
}