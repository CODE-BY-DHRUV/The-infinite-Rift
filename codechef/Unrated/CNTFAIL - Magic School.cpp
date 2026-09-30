import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        while (T-- > 0) {
            int N = sc.nextInt();

            int min = Integer.MAX_VALUE;
            int max = Integer.MIN_VALUE;
            int minCount = 0;
            int maxCount = 0;

            for (int i = 0; i < N; i++) {
                int x = sc.nextInt();

                if (x < min) {
                    min = x;
                    minCount = 1;
                } else if (x == min) {
                    minCount++;
                }

                if (x > max) {
                    max = x;
                    maxCount = 1;
                } else if (x == max) {
                    maxCount++;
                }
            }

            // All values are the same
            if (min == max) {
                if (min == 0) {
                    // Could be everyone failed OR only one student passed.
                    // For N > 1, everyone failed is conclusive.
                    if (N == 1) {
                        System.out.println(-1);
                    } else {
                        System.out.println(N);
                    }
                } else if (min == N - 1) {
                    // Everyone passed
                    System.out.println(0);
                } else {
                    // Impossible
                    System.out.println(-1);
                }
            }
            // Exactly two different values
            else {
                // Must differ by exactly 1
                if (max - min != 1) {
                    System.out.println(-1);
                    continue;
                }

                // max = P, min = P - 1
                int passed = minCount;
                int failed = maxCount;

                // Number of passed students must equal P (= max)
                if (passed == max) {
                    System.out.println(failed);
                } else {
                    System.out.println(-1);
                }
            }
        }

        sc.close();
    }
}
