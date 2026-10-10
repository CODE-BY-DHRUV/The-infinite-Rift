
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while (t-- > 0) {
            int consecutive = 0;
            boolean bored = false;

            for (int i = 0; i < 30; i++) {
                int day = sc.nextInt();

                if (day == 1) {
                    consecutive++;

                    if (consecutive > 5) {
                        bored = true;
                    }
                } else {
                    consecutive = 0;
                }
            }

            if (bored) {
                System.out.println("#coderlifematters");
            } else {
                System.out.println("#allcodersarefun");
            }
        }

        sc.close();
    }
}

