import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            int n = sc.nextInt();
            String s = sc.next();
            String r = sc.next();

            int changes = 0;

            for (int i = 0; i < n; i++) {
                if (s.charAt(i) != r.charAt(i)) {
                    changes++;
                }
            }

            // Bulb changes state for every button toggle.
            if (changes % 2 == 0) {
                System.out.println(1);
            } else {
                System.out.println(0);
            }
        }

        sc.close();
    }
}
