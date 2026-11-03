import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());

        StringBuilder sb = new StringBuilder();

        while (t-- > 0) {

            String s = br.readLine().trim();

            int countA = 0;
            int countB = 0;

            for (int i = 0; i < s.length(); i++) {

                if (s.charAt(i) == 'a') {
                    countA++;
                } else {
                    countB++;
                }
            }

            sb.append(Math.min(countA, countB)).append('\n');
        }

        System.out.print(sb);
    }
}