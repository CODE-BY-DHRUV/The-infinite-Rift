import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = sc.next();

        int[] freq = new int[26 * 26];

        for (int i = 0; i < s.length() - 1; i++) {
            int a = s.charAt(i) - 'a';
            int b = s.charAt(i + 1) - 'a';

            int pair = a * 26 + b;
            freq[pair]++;
        }

        int ans = 0;

        for (int count : freq) {
            if (count >= 2) {
                ans++;
            }
        }

        System.out.println(ans);
        sc.close();
    }
}