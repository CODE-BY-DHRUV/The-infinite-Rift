import java.io.*;
import java.util.*;

public class Main {

    static ArrayList<Long> fib = new ArrayList<>();

    static void generateFibonacci() {
        fib.add(1L);
        fib.add(2L);

        while (true) {
            int m = fib.size();
            long a = fib.get(m - 2);
            long b = fib.get(m - 1);

            if (b > 10_000_000_000L - a) {
                break;
            }

            long next = a + b;

            if (next >= 10_000_000_000L) {
                break;
            }

            fib.add(next);
        }
    }

    // Returns the smallest Fibonacci number
    // in the Zeckendorf representation of n.
    static long smallestFib(long n) {
        long smallest = -1;

        for (int i = fib.size() - 1; i >= 0; i--) {
            long f = fib.get(i);

            if (f <= n) {
                n -= f;
                smallest = f;
            }

            if (n == 0) {
                break;
            }
        }

        return smallest;
    }

    static boolean isFibonacci(long n) {
        return Collections.binarySearch(fib, n) >= 0;
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(
                new InputStreamReader(System.in)
        );

        generateFibonacci();

        StringBuilder out = new StringBuilder();

        while (true) {
            String line = br.readLine();

            if (line == null) {
                break;
            }

            line = line.trim();

            if (line.isEmpty()) {
                continue;
            }

            long n = Long.parseLong(line);

            if (n == 0) {
                break;
            }

            // First player cannot empty a pile of size 1.
            if (n == 1) {
                out.append("D\n");
                continue;
            }

            // Fibonacci starting positions are losing.
            if (isFibonacci(n)) {
                out.append("L\n");
                continue;
            }

            // Winning position:
            // smallest Fibonacci number in Zeckendorf representation.
            out.append(smallestFib(n)).append('\n');
        }

        System.out.print(out);
    }
}
