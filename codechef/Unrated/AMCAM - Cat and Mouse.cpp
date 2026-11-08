
import java.io.*;
import java.util.*;

public class Main {

    static class Point {
        int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static int N, K;
    static Point[] cats, mice;

    static boolean[][] forbidden;
    static int[] match;
    static boolean[] visited;

    // Maximum bipartite matching using Kuhn's algorithm
    static boolean dfs(int cat) {

        for (int mouse = 0; mouse < N; mouse++) {

            if (!forbidden[cat][mouse] || visited[mouse])
                continue;

            visited[mouse] = true;

            if (match[mouse] == -1 || dfs(match[mouse])) {
                match[mouse] = cat;
                return true;
            }
        }

        return false;
    }

    // Checks whether maximum distance D is achievable
    static boolean possible(long D) {

        forbidden = new boolean[N][N];

        // Build graph of forbidden cat-mouse pairs
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                long dx = cats[i].x - mice[j].x;
                long dy = cats[i].y - mice[j].y;

                long dist = dx * dx + dy * dy;

                if (dist > D) {
                    forbidden[i][j] = true;
                }
            }
        }

        match = new int[N];
        Arrays.fill(match, -1);

        int maxMatching = 0;

        // Find maximum bipartite matching
        for (int i = 0; i < N; i++) {

            visited = new boolean[N];

            if (dfs(i)) {
                maxMatching++;
            }
        }

        // Maximum valid animals = 2*N - maximum matching
        return (2 * N - maxMatching) >= K;
    }

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        cats = new Point[N];
        mice = new Point[N];

        for (int i = 0; i < N; i++) {

            st = new StringTokenizer(br.readLine());

            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());

            cats[i] = new Point(x, y);
        }

        for (int i = 0; i < N; i++) {

            st = new StringTokenizer(br.readLine());

            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());

            mice[i] = new Point(x, y);
        }

        // Collect all possible squared distances
        long[] distances = new long[N * N];

        int idx = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                long dx = cats[i].x - mice[j].x;
                long dy = cats[i].y - mice[j].y;

                distances[idx++] = dx * dx + dy * dy;
            }
        }

        Arrays.sort(distances);

        // Binary search for minimum feasible squared distance
        int low = 0;
        int high = distances.length - 1;

        while (low < high) {

            int mid = low + (high - low) / 2;

            if (possible(distances[mid])) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        double answer = Math.sqrt(distances[low]);

        System.out.printf("%.12f%n", answer);
    }
}
