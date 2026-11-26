import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = Integer.parseInt(sc.nextLine());

        while (t-- > 0) {
            String s = sc.nextLine();
            StringBuilder result = new StringBuilder();

            String[] words = s.split(" ");

            for (int i = 0; i < words.length; i++) {
                String word = words[i];

                // Check if the word is entirely uppercase
                if (word.equals(word.toUpperCase())) {
                    result.append(word);
                } else {
                    // Convert first letter to uppercase and remaining to lowercase
                    result.append(Character.toUpperCase(word.charAt(0)));
                    result.append(word.substring(1).toLowerCase());
                }

                if (i < words.length - 1) {
                    result.append(" ");
                }
            }

            System.out.println(result);
        }

        sc.close();
    }
}