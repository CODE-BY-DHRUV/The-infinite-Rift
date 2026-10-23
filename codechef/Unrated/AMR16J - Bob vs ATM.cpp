import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            String s = br.readLine().trim();
            int n = s.length();

            int[] stack = new int[n];
            int[] childXor = new int[n];
            int[] grundy = new int[n];
            int top = -1;

            int totalXor = 0;

            for (int i = 0; i < n; i++) {
                if (s.charAt(i) == '(') {
                    stack[++top] = i;
                } else {
                    int node = stack[top--];

                    // Grundy number of this bracket pair's subtree
                    grundy[node] = childXor[node] + 1;

                    if (top >= 0) {
                        int parent = stack[top];
                        childXor[parent] ^= grundy[node];
                    } else {
                        // A top-level primitive bracket sequence
                        totalXor ^= grundy[node];
                    }
                }
            }

            out.append(totalXor != 0 ? "ATM" : "Bob")
               .append('\n');
        }

        System.out.print(out);
    }
}