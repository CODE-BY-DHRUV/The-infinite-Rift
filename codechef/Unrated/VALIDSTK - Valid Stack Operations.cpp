import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();

        while (T-- > 0) {
            int n = sc.nextInt();

            int size = 0;
            boolean valid = true;

            for (int i = 0; i < n; i++) {
                int operation = sc.nextInt();

                if (operation == 1) {
                    size++;
                } else {
                    if (size == 0) {
                        valid = false;
                    } else {
                        size--;
                    }
                }
            }

            System.out.println(valid ? "Valid" : "Invalid");
        }

        sc.close();
    }
}