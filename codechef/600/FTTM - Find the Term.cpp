
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String S = sc.nextLine();
        String T = sc.nextLine();

        if (S.contains(T)) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }

        sc.close();
    }
}

