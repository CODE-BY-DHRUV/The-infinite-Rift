
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        String line = br.readLine();
        if (line == null) return;
        st = new StringTokenizer(line);
        if (!st.hasMoreTokens()) return;
        int tCases = Integer.parseInt(st.nextToken());

        StringBuilder out = new StringBuilder();

        for (int tc = 0; tc < tCases; tc++) {
            line = br.readLine();
            while (line != null && line.trim().isEmpty()) {
                line = br.readLine();
            }
            if (line == null) break;
            st = new StringTokenizer(line);
            int n = Integer.parseInt(st.nextToken());

            long tPrev = 0;
            int x1Prev = 1, y1Prev = 1;
            int x2Prev = 2, y2Prev = 1;

            boolean possible = true;

            for (int i = 0; i < n; i++) {
                line = br.readLine();
                while (line != null && line.trim().isEmpty()) {
                    line = br.readLine();
                }
                st = new StringTokenizer(line);
                long ti = Long.parseLong(st.nextToken());
                int x1 = Integer.parseInt(st.nextToken());
                int y1 = Integer.parseInt(st.nextToken());
                int x2 = Integer.parseInt(st.nextToken());
                int y2 = Integer.parseInt(st.nextToken());

                if (!possible) {
                    continue;
                }

                // Check collision at instant ti
                if (x1 == x2 && y1 == y2) {
                    possible = false;
                }

                long dt = ti - tPrev;

                // Check Car 1 movement constraints
                long dy1 = y1 - y1Prev;
                long diff1 = (x1Prev != x1) ? 1 : 0;
                if (dy1 < 0 || dt < dy1 + diff1) {
                    possible = false;
                }

                // Check Car 2 movement constraints
                long dy2 = y2 - y2Prev;
                long diff2 = (x2Prev != x2) ? 1 : 0;
                if (dy2 < 0 || dt < dy2 + diff2) {
                    possible = false;
                }

                // Update previous positions and time
                tPrev = ti;
                x1Prev = x1;
                y1Prev = y1;
                x2Prev = x2;
                y2Prev = y2;
            }

            if (possible) {
                out.append("yes\n");
            } else {
                out.append("no\n");
            }
        }
        System.out.print(out);
    }
}