
import java.io.*;
import java.util.*;

public class Main {

    static final int LIMIT = 600000;

    static class Segment {
        int terminalMask;
        long fixedProduct;
        int oddCount, evenCount;
        boolean zeroProduct;

        Segment(String s) {
            StringTokenizer st = new StringTokenizer(s);
            String previous = null;

            fixedProduct = 1;

            while (st.hasMoreTokens()) {
                String current = st.nextToken();

                if (previous != null) {
                    processDirective(previous);
                }

                previous = current;
            }

            terminalMask = mask(previous);
        }

        void processDirective(String word) {
            if (word.equals("odd")) {
                oddCount++;
            } else if (word.equals("even")) {
                evenCount++;
            } else {
                int d = digit(word);

                if (d == 0) {
                    zeroProduct = true;
                } else if (!zeroProduct) {
                    fixedProduct *= d;

                    if (fixedProduct > LIMIT) {
                        fixedProduct = LIMIT + 1L;
                    }
                }
            }
        }
    }

    static int digit(String s) {
        switch (s) {
            case "zero": return 0;
            case "one": return 1;
            case "two": return 2;
            case "three": return 3;
            case "four": return 4;
            case "five": return 5;
            case "six": return 6;
            case "seven": return 7;
            case "eight": return 8;
            case "nine": return 9;
            default: return -1;
        }
    }

    // Bit d represents the digit d.
    static int mask(String s) {
        int d = digit(s);

        if (d >= 0) {
            return 1 << d;
        }

        if (s.equals("odd")) {
            return (1 << 1) | (1 << 3) | (1 << 5)
                    | (1 << 7) | (1 << 9);
        }

        return (1 << 0) | (1 << 2) | (1 << 4)
                | (1 << 6) | (1 << 8);
    }

    static boolean matches(Segment s, int digit, int len) {
        if ((s.terminalMask & (1 << digit)) == 0) {
            return false;
        }

        if (s.zeroProduct || s.fixedProduct > len) {
            return false;
        }

        if (len % s.fixedProduct != 0) {
            return false;
        }

        int x = (int) (len / s.fixedProduct);

        int a2 = 0, a3 = 0, a5 = 0, a7 = 0;

        while (x % 2 == 0) {
            a2++;
            x /= 2;
        }
        while (x % 3 == 0) {
            a3++;
            x /= 3;
        }
        while (x % 5 == 0) {
            a5++;
            x /= 5;
        }
        while (x % 7 == 0) {
            a7++;
            x /= 7;
        }

        // No literal can produce a prime factor other than 2, 3, 5, 7.
        if (x != 1) {
            return false;
        }

        // Try the number of even directives that choose 6.
        for (int b = 0; b <= Math.min(a3, s.evenCount); b++) {
            int remainingEven = s.evenCount - b;
            int remainingTwos = a2 - b;
            int remainingThrees = a3 - b;

            if (remainingTwos < 0) {
                continue;
            }

            // Each remaining even directive contributes 1 to 3 factors of 2.
            if (remainingTwos < remainingEven
                    || remainingTwos > 3 * remainingEven) {
                continue;
            }

            // Odd directives can produce 3, 9, 5 and 7.
            int minOddDirectives =
                    (remainingThrees + 1) / 2 + a5 + a7;

            if (minOddDirectives <= s.oddCount) {
                return true;
            }
        }

        return false;
    }

    static List<Segment> parseRiddle(String riddle) {
        List<Segment> segments = new ArrayList<>();
        int start = 0;

        for (int i = 0; i < riddle.length(); i++) {
            char c = riddle.charAt(i);

            if (c == ',' || c == '.') {
                String part = riddle.substring(start, i).trim();

                if (!part.isEmpty()) {
                    segments.add(new Segment(part));
                }

                start = i + 1;
            }
        }

        return segments;
    }

    static boolean solve(String riddle, String password) {
        List<Segment> segments = parseRiddle(riddle);

        // Compress the password into consecutive runs of equal digits.
        List<Integer> digits = new ArrayList<>();
        List<Integer> lengths = new ArrayList<>();

        for (int i = 0; i < password.length();) {
            int j = i + 1;

            while (j < password.length()
                    && password.charAt(j) == password.charAt(i)) {
                j++;
            }

            digits.add(password.charAt(i) - '0');
            lengths.add(j - i);
            i = j;
        }

        // Every password run must match a segment.
        // Segments may be skipped, so choose the earliest compatible segment.
        int p = 0;

        for (int i = 0; i < digits.size(); i++) {
            int d = digits.get(i);
            int len = lengths.get(i);
            boolean found = false;

            while (p < segments.size()) {
                Segment s = segments.get(p++);

                if (matches(s, d, len)) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
                new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        for (int tc = 1; tc <= T; tc++) {
            String riddle = br.readLine();

            while (riddle != null && riddle.trim().isEmpty()) {
                riddle = br.readLine();
            }

            int n = Integer.parseInt(br.readLine().trim());
            String password = br.readLine().trim();

            boolean ok = solve(riddle, password);

            out.append("Case ").append(tc).append(": ")
               .append(ok ? "MAY BE" : "NO").append('\n');
        }

        System.out.print(out);
    }
}
