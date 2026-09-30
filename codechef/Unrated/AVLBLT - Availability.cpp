import java.io.*;
import java.util.*;

public class Main {

    static final int DAY = 1440;
    static final int WEEK = 7 * DAY;

    static int toMinutes(String s) {
        return Integer.parseInt(s.substring(0, 2)) * 60
                + Integer.parseInt(s.substring(3, 5));
    }

    static String toTime(int x) {
        if (x == DAY) {
            return "00:00";
        }

        int h = x / 60;
        int m = x % 60;

        return String.format("%02d:%02d", h, m);
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(
                new InputStreamReader(System.in)
        );

        // IMPORTANT:
        // First line is timezone, NOT number of test cases.
        int timezone = Integer.parseInt(br.readLine().trim());
        int shift = timezone * 60;

        // Each interval is stored as:
        // [start, end) in absolute week minutes.
        List<int[]> intervals = new ArrayList<>();

        for (int day = 0; day < 7; day++) {

            int k = Integer.parseInt(br.readLine().trim());

            for (int i = 0; i < k; i++) {

                StringTokenizer st =
                        new StringTokenizer(br.readLine());

                String s = st.nextToken();
                String e = st.nextToken();

                int start = toMinutes(s);
                int end = toMinutes(e);

                // 00:00 as end means end of the day.
                if (end == 0) {
                    end = DAY;
                }

                int absoluteStart = day * DAY + start;
                int absoluteEnd = day * DAY + end;

                // Subtract timezone.
                absoluteStart -= shift;
                absoluteEnd -= shift;

                // Normalize the interval to [0, WEEK).
                while (absoluteStart < 0) {
                    absoluteStart += WEEK;
                    absoluteEnd += WEEK;
                }

                while (absoluteStart >= WEEK) {
                    absoluteStart -= WEEK;
                    absoluteEnd -= WEEK;
                }

                // If interval crosses Saturday -> Sunday.
                if (absoluteEnd > WEEK) {
                    intervals.add(new int[]{
                            absoluteStart,
                            WEEK
                    });

                    intervals.add(new int[]{
                            0,
                            absoluteEnd - WEEK
                    });
                } else {
                    intervals.add(new int[]{
                            absoluteStart,
                            absoluteEnd
                    });
                }
            }
        }

        // Sort by starting time.
        intervals.sort((a, b) -> {
            if (a[0] != b[0]) {
                return Integer.compare(a[0], b[0]);
            }
            return Integer.compare(a[1], b[1]);
        });

        // Merge overlapping/adjacent intervals.
        List<int[]> merged = new ArrayList<>();

        for (int[] cur : intervals) {

            if (merged.isEmpty()) {
                merged.add(cur);
            } else {
                int[] last = merged.get(merged.size() - 1);

                if (cur[0] <= last[1]) {
                    last[1] = Math.max(last[1], cur[1]);
                } else {
                    merged.add(cur);
                }
            }
        }

        // Prepare intervals for each day.
        List<int[]>[] answer = new ArrayList[7];

        for (int i = 0; i < 7; i++) {
            answer[i] = new ArrayList<>();
        }

        for (int[] interval : merged) {

            int start = interval[0];
            int end = interval[1];

            while (start < end) {

                int day = start / DAY;

                int dayStart = day * DAY;
                int dayEnd = Math.min(end, dayStart + DAY);

                int startTime = start - dayStart;
                int endTime = dayEnd - dayStart;

                answer[day].add(new int[]{
                        startTime,
                        endTime
                });

                start = dayEnd;
            }
        }

        // Output exactly 7 blocks.
        StringBuilder out = new StringBuilder();

        for (int day = 0; day < 7; day++) {

            out.append(answer[day].size()).append('\n');

            for (int[] interval : answer[day]) {

                out.append(toTime(interval[0]))
                   .append(' ')
                   .append(toTime(interval[1]))
                   .append('\n');
            }
        }

        System.out.print(out);
    }
}