import java.io.*;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class Main {
    static final long MOD = 1_000_000_007L;
    static final long INV4 = 250_000_002L;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            BigInteger N = new BigInteger(st.nextToken());
            long C = Long.parseLong(st.nextToken());

            BigInteger n2 = N.multiply(N);
            BigInteger total = n2.multiply(BigInteger.valueOf(5));

            BigInteger odd = N.testBit(0)
                    ? BigInteger.ONE
                    : BigInteger.ZERO;

            BigInteger e90 = total.add(odd.multiply(
                    BigInteger.valueOf(3))).divide(
                    BigInteger.valueOf(4));

            BigInteger e180 = total.add(odd).divide(
                    BigInteger.valueOf(2));

            long f0 = BigInteger.valueOf(C).modPow(
                    total, BigInteger.valueOf(MOD)
            ).longValue();

            long f90 = BigInteger.valueOf(C).modPow(
                    e90, BigInteger.valueOf(MOD)
            ).longValue();

            long f180 = BigInteger.valueOf(C).modPow(
                    e180, BigInteger.valueOf(MOD)
            ).longValue();

            long sum = (f0 + 2L * f90 % MOD + f180) % MOD;
            long ans = sum * INV4 % MOD;

            out.append(ans).append('\n');
        }

        System.out.print(out);
    }
}