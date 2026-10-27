
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();

        while (T-- > 0) {
            int x1 = sc.nextInt();
            int y1 = sc.nextInt();
            int x2 = sc.nextInt();
            int y2 = sc.nextInt();

            if (y1 == y2 && x1 < x2) {
                System.out.println("right");
            } else if (y1 == y2 && x1 > x2) {
                System.out.println("left");
            } else if (x1 == x2 && y1 < y2) {
                System.out.println("up");
            } else if (x1 == x2 && y1 > y2) {
                System.out.println("down");
            } else {
                System.out.println("sad");
            }
        }

        sc.close();
    }
}
