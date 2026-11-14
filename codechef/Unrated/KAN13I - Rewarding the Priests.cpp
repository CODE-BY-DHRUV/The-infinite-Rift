
import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Main {

    static BigInteger ZERO = BigInteger.ZERO;
    static BigInteger ONE = BigInteger.ONE;

    static class Fraction {
        BigInteger num, den;

        Fraction(BigInteger num, BigInteger den) {
            this.num = num;
            this.den = den;
        }
    }

    // Convert time into exact elapsed seconds
    static Fraction getTime(
            int h, int m, int s,
            int sn, int sd, int H, int M) {

        long base = (long) (h % H) * M * M
                  + (long) m * M
                  + s;

        BigInteger den = BigInteger.valueOf(sd);

        BigInteger num = BigInteger.valueOf(base)
                .multiply(den)
                .add(BigInteger.valueOf(sn));

        return new Fraction(num, den);
    }

    // Compare two fractions
    static int compare(Fraction a, Fraction b) {

        BigInteger left = a.num.multiply(b.den);
        BigInteger right = b.num.multiply(a.den);

        return left.compareTo(right);
    }

    // Add one complete day
    static void addDay(Fraction f, long day) {

        f.num = f.num.add(
            BigInteger.valueOf(day).multiply(f.den)
        );
    }

    // Floor division for non-negative numbers
    static BigInteger floorDiv(BigInteger a, BigInteger b) {
        return a.divide(b);
    }

    // Ceiling division for non-negative numbers
    static BigInteger ceilDiv(BigInteger a, BigInteger b) {

        return a.add(b).subtract(ONE).divide(b);
    }

    // Calculate number of valid swapping times
    static BigInteger solve(
            int H, int M,
            Fraction start, Fraction finish) {

        long day = (long) H * M * M;

        // Handle crossing midnight
        if (compare(finish, start) < 0) {
            addDay(finish, day);
        }

        // F(t) = t * (H^2 - 1) / (H * M^2)

        BigInteger factor = BigInteger.valueOf(
            (long) H * H - 1
        );

        BigInteger denominator = BigInteger.valueOf(day);

        // F(start)
        BigInteger startNum = start.num.multiply(factor);
        BigInteger startDen = start.den.multiply(denominator);

        // F(finish)
        BigInteger endNum = finish.num.multiply(factor);
        BigInteger endDen = finish.den.multiply(denominator);

        // ceil(F(start))
        BigInteger first = ceilDiv(startNum, startDen);

        // floor(F(finish))
        BigInteger last = floorDiv(endNum, endDen);

        BigInteger answer = last.subtract(first).add(ONE);

        return answer.max(ZERO);
    }

    public static void main(String[] args) throws IOException {

        FastScanner fs = new FastScanner(System.in);

        int T = fs.nextInt();

        StringBuilder sb = new StringBuilder();

        for (int tc = 1; tc <= T; tc++) {

            int H = fs.nextInt();
            int M = fs.nextInt();

            int h1 = fs.nextInt();
            int m1 = fs.nextInt();
            int s1 = fs.nextInt();
            int sn1 = fs.nextInt();
            int sd1 = fs.nextInt();

            int h2 = fs.nextInt();
            int m2 = fs.nextInt();
            int s2 = fs.nextInt();
            int sn2 = fs.nextInt();
            int sd2 = fs.nextInt();

            Fraction start = getTime(
                h1, m1, s1, sn1, sd1, H, M
            );

            Fraction finish = getTime(
                h2, m2, s2, sn2, sd2, H, M
            );

            BigInteger ans = solve(
                H, M, start, finish
            );

            sb.append("Case ")
              .append(tc)
              .append(": ")
              .append(ans)
              .append('\n');
        }

        System.out.print(sb);
    }

    static class FastScanner {

        BufferedReader br;
        StringTokenizer st;

        FastScanner(InputStream in) {
            br = new BufferedReader(
                new InputStreamReader(in)
            );
        }

        String next() throws IOException {

            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }

            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
}
