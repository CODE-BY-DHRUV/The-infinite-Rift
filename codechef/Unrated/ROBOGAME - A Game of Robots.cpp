
import java.io.*;
import java.util.*;

public class Main {

    static class Robot {
        int left, right;

        Robot(int left, int right) {
            this.left = left;
            this.right = right;
        }
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (T-- > 0) {
            String s = br.readLine().trim();
            int n = s.length();

            List<Robot> robots = new ArrayList<>();

            for (int i = 0; i < n; i++) {
                if (s.charAt(i) == '.') {
                    continue;
                }

                int d = s.charAt(i) - '0';

                int left = Math.max(0, i - d);
                int right = Math.min(n - 1, i + d);

                robots.add(new Robot(left, right));
            }

            boolean safe = true;

            // Check whether any two ranges overlap.
            for (int i = 0; i < robots.size() && safe; i++) {
                for (int j = i + 1; j < robots.size(); j++) {
                    Robot a = robots.get(i);
                    Robot b = robots.get(j);

                    if (Math.max(a.left, b.left) <= Math.min(a.right, b.right)) {
                        safe = false;
                        break;
                    }
                }
            }

            out.append(safe ? "safe\n" : "unsafe\n");
        }

        System.out.print(out);
    }
}


