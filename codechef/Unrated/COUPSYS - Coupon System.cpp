import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        while (T-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());

            // Index 1, 2, 3 represent the levels
            int[] maxDiscount = new int[4];
            int[] bestCity = new int[4];

            // Discount starts at 0, city starts at a large value
            Arrays.fill(bestCity, Integer.MAX_VALUE);

            for (int i = 0; i < n; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());

                int city = Integer.parseInt(st.nextToken());
                int level = Integer.parseInt(st.nextToken());
                int discount = Integer.parseInt(st.nextToken());

                if (discount > maxDiscount[level]) {
                    maxDiscount[level] = discount;
                    bestCity[level] = city;
                } 
                else if (discount == maxDiscount[level] && city < bestCity[level]) {
                    bestCity[level] = city;
                }
            }

            for (int level = 1; level <= 3; level++) {
                System.out.println(maxDiscount[level] + " " + bestCity[level]);
            }
        }
    }
}