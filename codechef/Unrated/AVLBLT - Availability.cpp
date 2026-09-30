import java.io.*;
import java.util.*;

public class Main {

    static final int DAY = 24 * 60;
    static final int WEEK = 7 * DAY;

    static int toMinutes(String s) {
        int h = Integer.parseInt(s.substring(0, 2));
        int m = Integer.parseInt(s.substring(3, 5));
        return h * 60 + m;
    }

    static String toTime(int minutes) {
        minutes %= DAY;

        int h = minutes / 60;
        int m = minutes % 60;

        return String.format("%02d:%02d", h, m);
    }

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());

        // Store availability as intervals for each day.
        // Each interval is [start, end), where end can be 1440.
        List<int[]>[] days = new ArrayList[7];

        for (int i = 0; i < 7; i++) {
            days[i] = new ArrayList<>();
        }

        for (int day = 0; day < 7; day++) {

            int k = Integer.parseInt(br.readLine().trim());

            for (int i = 0; i < k; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());

                int start = toMinutes(st.nextToken());
                int end = toMinutes(st.nextToken());

                // 00:00 as the end time means midnight at
                // the END of the day, i.e. 1440.
                if (end == 0) {
                    end = DAY;
                }

                days[day].add(new int[]{start, end});
            }
        }

        int shift = T * 60;

        // Result intervals for each day.
        List<int[]>[] result = new ArrayList[7];

        for (int i = 0; i < 7; i++) {
            result[i] = new ArrayList<>();
        }

        /*
         * Convert every interval into absolute week minutes.
         *
         * Sunday 00:00 = 0
         * Monday 00:00 = 1440
         * ...
         *
         * Then subtract the timezone shift.
         */
        for (int day = 0; day < 7; day++) {

            for (int[] interval : days[day]) {

                int start = day * DAY + interval[0];
                int end = day * DAY + interval[1];

                int newStart = start - shift;
                int newEnd = end - shift;

                /*
                 * Because the week is cyclic, an interval can
                 * cross the beginning or end of the week.
                 *
                 * Normalize it by considering three copies of
                 * the week and then keeping the middle copy.
                 */
                addInterval(result, newStart, newEnd);
            }
        }

        // Merge overlapping/adjacent intervals on every day.
        for (int day = 0; day < 7; day++) {
            result[day].sort(Comparator.comparingInt(a -> a[0]));

            List<int[]> merged = new ArrayList<>();

            for (int[] cur : result[day]) {

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

            result[day] = merged;
        }

        // Print exactly 7 blocks.
        StringBuilder out = new StringBuilder();

        for (int day = 0; day < 7; day++) {

            out.append(result[day].size()).append('\n');

            for (int[] interval : result[day]) {

                int start = interval[0];
                int end = interval[1];

                out.append(toTime(start))
                   .append(' ')
                   .append(toTime(end))
                   .append('\n');
            }
        }

        System.out.print(out);
    }

    /*
     * Add an interval [start, end) to the cyclic week.
     *
     * We split it at week boundaries and put the pieces
     * into the appropriate day.
     */
    static void addInterval(List<int[]>[] result, int start, int end) {

        // The interval length is at most 24 hours, but after
        // shifting it can cross the week boundary.

        while (start < 0) {
            start += WEEK;
            end += WEEK;
        }

        while (start >= WEEK) {
            start -= WEEK;
            end -= WEEK;
        }

        // Normal interval inside the week.
        if (end <= WEEK) {
            addToDays(result, start, end);
        } else {
            // Crosses the end of Saturday.
            addToDays(result, start, WEEK);
            addToDays(result, 0, end - WEEK);
        }
    }

    static void addToDays(List<int[]>[] result, int start, int end) {

        while (start < end) {

            int day = start / DAY;
            int dayEnd = Math.min(end, (day + 1) * DAY);

            int startInDay = start % DAY;
            int endInDay = dayEnd % DAY;

            if (endInDay == 0) {
                endInDay = DAY;
            }

            result[day].add(new int[]{
                startInDay,
                endInDay
            });

            start = dayEnd;
        }
    }
}