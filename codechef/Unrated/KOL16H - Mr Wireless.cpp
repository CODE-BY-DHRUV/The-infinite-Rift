import java.io.*;
import java.math.BigInteger;

public class Main {
    static final long MOD = 1L << 33;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        for (int tc = 1; tc <= T; tc++) {
            BigInteger n = new BigInteger(br.readLine().trim());

            long answer;

            if (n.compareTo(BigInteger.valueOf(33)) >= 0) {
                answer = MOD - 1;
            } else {
                int exponent = n.intValue();
                answer = ((1L << exponent) - 1) % MOD;
            }

            out.append("Case ").append(tc)
               .append(": ").append(answer).append('\n');
        }

        System.out.print(out);
    }
}
