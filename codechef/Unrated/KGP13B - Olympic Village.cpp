
import java.io.*;
import java.util.*;

public class Main {

    static class EventPoint {
        int day;
        int change;

        EventPoint(int day, int change) {
            this.day = day;
            this.change = change;
        }
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int T = fs.nextInt();

        for (int tc = 1; tc <= T; tc++) {

            int K = fs.nextInt();
            int M = fs.nextInt();

            int[] start = new int[K];
            int[] end = new int[K];
            int[] participants = new int[K];

            for (int i = 0; i < K; i++) {
                start[i] = fs.nextInt();
                end[i] = fs.nextInt();
            }

            // Read country participation information
            for (int i = 0; i < M; i++) {

                int D = fs.nextInt();

                for (int j = 0; j < D; j++) {

                    int eventId = fs.nextInt() - 1;
                    int count = fs.nextInt();

                    participants[eventId] += count;
                }
            }

            // Create start and end points
            ArrayList<EventPoint> points = new ArrayList<>();

            for (int i = 0; i < K; i++) {

                points.add(
                    new EventPoint(start[i], participants[i])
                );

                points.add(
                    new EventPoint(end[i], -participants[i])
                );
            }

            // Sort by day.
            // For equal days, process starts before ends.
            points.sort((a, b) -> {
                if (a.day != b.day) {
                    return Integer.compare(a.day, b.day);
                }

                return Integer.compare(b.change, a.change);
            });

            int currentBeds = 0;
            int answer = 0;

            // Sweep line
            for (EventPoint p : points) {

                currentBeds += p.change;

                answer = Math.max(answer, currentBeds);
            }

            out.append("Case ")
               .append(tc)
               .append(": ")
               .append(answer)
               .append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {

        BufferedReader br;
        StringTokenizer st;

        FastScanner(InputStream in) {
            br = new BufferedReader(
                new InputStreamReader(in)
            );
        }

        String next() throws IOException {

            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }

            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
}
