
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
                new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        for (int tc = 1; tc <= T; tc++) {
            String[] bounds = br.readLine().trim().split("\\s+");
            int M = Integer.parseInt(bounds[0]);
            int N = Integer.parseInt(bounds[1]);

            String[] target = br.readLine().trim().split("\\s+");
            int Rx = Integer.parseInt(target[0]);
            int Ry = Integer.parseInt(target[1]);

            int length = Integer.parseInt(br.readLine().trim());
            String moves = br.readLine().trim();

            int x = 0, y = 0;

            for (int i = 0; i < length; i++) {
                char c = moves.charAt(i);

                switch (c) {
                    case 'U': y++; break;
                    case 'D': y--; break;
                    case 'R': x++; break;
                    case 'L': x--; break;
                }
            }

            String answer;

            if (x < 0 || x > M || y < 0 || y > N) {
                answer = "DANGER";
            } else if (x == Rx && y == Ry) {
                answer = "REACHED";
            } else {
                answer = "SOMEWHERE";
            }

            System.out.println("Case " + tc + ": " + answer);
        }
    }
}
