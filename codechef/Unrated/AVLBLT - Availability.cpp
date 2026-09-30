import java.io.*;
import java.util.*;

public class Main {

    static final int DAY = 1440;
    static final int WEEK = 10080;

    static int parseTime(String s) {
        return Integer.parseInt(s.substring(0, 2)) * 60
             + Integer.parseInt(s.substring(3, 5));
    }

    static String formatTime(int x) {
        if (x == 1440) {
            return "00:00";
        }

        int h = x / 60;
        int m = x % 60;

        return String.format("%02d:%02d", h, m);
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br =
                new BufferedReader(new InputStreamReader(System.in));

        String first = br.readLine();

        if (first == null || first.trim().isEmpty()) {
            return;
        }

        int timezone = Integer.parseInt(first.trim());
        int shift = timezone * 60;

        boolean[] available = new boolean[WEEK];

        // Read Sunday to Saturday
        for (int day = 0; day < 7; day++) {

            String line = br.readLine();

            while (line != null && line.trim().isEmpty()) {
                line = br.readLine();
            }

            if (line == null) {
                return;
            }

            int k = Integer.parseInt(line.trim());

            for (int j = 0; j < k; j++) {

                String intervalLine = br.readLine();

                while (intervalLine != null &&
                       intervalLine.trim().isEmpty()) {
                    intervalLine = br.readLine();
                }

                if (intervalLine == null) {
                    return;
                }

                StringTokenizer st =
                        new StringTokenizer(intervalLine);

                String startString = st.nextToken();
                String endString = st.nextToken();

                int start = parseTime(startString);
                int end = parseTime(endString);

                // 00:00 as end means end of day.
                if (end == 0) {
                    end = DAY;
                }

                int base = day * DAY;

                for (int minute = start; minute < end; minute++) {
                    available[base + minute] = true;
                }
            }
        }

        // Shift everything backwards by timezone.
        boolean[] result = new boolean[WEEK];

        for (int i = 0; i < WEEK; i++) {

            if (available[i]) {

                int newPos = i - shift;

                if (newPos < 0) {
                    newPos += WEEK;
                }

                result[newPos] = true;
            }
        }

        StringBuilder output = new StringBuilder();

        // Print Sunday through Saturday.
        for (int day = 0; day < 7; day++) {

            int base = day * DAY;

            List<int[]> intervals = new ArrayList<>();

            int i = 0;

            while (i < DAY) {

                if (!result[base + i]) {
                    i++;
                    continue;
                }

                int start = i;

                while (i < DAY && result[base + i]) {
                    i++;
                }

                int end = i;

                intervals.add(new int[]{start, end});
            }

            output.append(intervals.size()).append('\n');

            for (int[] interval : intervals) {

                output.append(formatTime(interval[0]))
                      .append(' ')
                      .append(formatTime(interval[1]))
                      .append('\n');
            }
        }

        System.out.print(output);
    }
}