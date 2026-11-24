import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String s = sc.next();
        int n = sc.nextInt();

        boolean[] known = new boolean[26];

        for (char c : s.toCharArray()) {
            known[c - 'a'] = true;
        }

        StringBuilder ans = new StringBuilder();

        while (n-- > 0) {
            String word = sc.next();
            boolean canRead = true;

            for (char c : word.toCharArray()) {
                if (!known[c - 'a']) {
                    canRead = false;
                    break;
                }
            }

            ans.append(canRead ? "Yes" : "No").append('\n');
        }

        System.out.print(ans);
        sc.close();
    }
}
