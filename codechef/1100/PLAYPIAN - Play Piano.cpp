
import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            String s = sc.next();

            boolean valid = true;

            for (int i = 0; i < s.length(); i += 2) {
                if (s.charAt(i) == s.charAt(i + 1)) {
                    valid = false;
                    break;
                }
            }

            System.out.println(valid ? "yes" : "no");
        }

        sc.close();
    }
}
