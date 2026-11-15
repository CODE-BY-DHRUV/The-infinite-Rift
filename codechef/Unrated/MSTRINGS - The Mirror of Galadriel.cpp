
import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            String s = sc.next();

            boolean magical = true;

            for (int i = 0; i < s.length() - 1; i++) {
                String pair = s.substring(i, i + 2);
                String reverse = new StringBuilder(pair).reverse().toString();

                if (!s.contains(reverse)) {
                    magical = false;
                    break;
                }
            }

            System.out.println(magical ? "YES" : "NO");
        }

        sc.close();
    }
}
