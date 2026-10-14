import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();

        while (t-- > 0) {
            String s = sc.next();
            int transitions = 0;

            for (int i = 0; i < 8; i++) {
                if (s.charAt(i) != s.charAt((i + 1) % 8)) {
                    transitions++;
                }
            }

            System.out.println(transitions <= 2 ? "uniform" : "non-uniform");
        }

        sc.close();
    }
}