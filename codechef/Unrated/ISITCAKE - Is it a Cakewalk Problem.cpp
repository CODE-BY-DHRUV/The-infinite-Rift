import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        while (T-- > 0) {
            int count = 0;

            // Read 100 times (10 x 10 grid)
            for (int i = 0; i < 100; i++) {
                int time = sc.nextInt();

                if (time <= 30) {
                    count++;
                }
            }

            if (count >= 60) {
                System.out.println("yes");
            } else {
                System.out.println("no");
            }
        }

        sc.close();
    }
}