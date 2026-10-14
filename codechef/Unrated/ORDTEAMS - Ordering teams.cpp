import java.util.*;

public class Main {
    static boolean better(int[] a, int[] b) {
        boolean strictlyBetter = false;

        for (int i = 0; i < 3; i++) {
            if (a[i] < b[i]) {
                return false;
            }
            if (a[i] > b[i]) {
                strictlyBetter = true;
            }
        }

        return strictlyBetter;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        while (t-- > 0) {
            int[][] p = new int[3][3];

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    p[i][j] = sc.nextInt();
                }
            }

            boolean possible = false;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (i != j && j != k && i != k
                                && better(p[j], p[i])
                                && better(p[k], p[j])) {
                            possible = true;
                        }
                    }
                }
            }

            System.out.println(possible ? "yes" : "no");
        }

        sc.close();
    }
}