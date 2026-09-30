import java.io.*;
import java.util.*;

public class Main {
    static final int DAY = 24 * 60;
    static final int WEEK = 7 * DAY;

    static int toMinutes(String s) {
        int h = (s.charAt(0) - '0') * 10 + (s.charAt(1) - '0');
        int m = (s.charAt(3) - '0') * 10 + (s.charAt(4) - '0');
        return h * 60 + m;
    }

    static String toTime(int x) {
        if (x == DAY) {
            return "00:00";
        }

        int h = x / 60;
        int m = x % 60;

        return String.format("%02d:%02d", h, m);
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        // First line = friend's timezone
        int timezone = sc.nextInt();

        int shift = timezone * 60;

        // availability[minute] tells whether the friend
        // is available at that minute in the original timezone.
        boolean[] availability = new boolean[WEEK];

        // Read 7 days: Sunday ... Saturday
        for (int day = 0; day < 7; day++) {

            int k = sc.nextInt();

            for (int i = 0; i < k; i++) {

                String startString = sc.next();
                String endString = sc.next();

                int start = toMinutes(startString);
                int end = toMinutes(endString);

                /*
                 * Special case:
                 * 00:00 as an END means midnight at the
                 * end of the day.
                 */
                if (end == 0) {
                    end = DAY;
                }

                int base = day * DAY;

                for (int minute = start; minute < end; minute++) {
                    availability[base + minute] = true;
                }
            }
        }

        /*
         * Translate to our timezone.
         *
         * Friend's time - timezone difference.
         *
         * Example:
         * friend's 12:00 with T = 6
         * becomes our 06:00.
         */
        boolean[] translated = new boolean[WEEK];

        for (int minute = 0; minute < WEEK; minute++) {

            if (availability[minute]) {

                int newMinute = minute - shift;

                // Wrap around the week.
                if (newMinute < 0) {
                    newMinute += WEEK;
                }

                translated[newMinute] = true;
            }
        }

        StringBuilder ans = new StringBuilder();

        /*
         * Convert the boolean representation back into
         * intervals for each of the 7 days.
         */
        for (int day = 0; day < 7; day++) {

            int dayStart = day * DAY;
            int dayEnd = dayStart + DAY;

            List<int[]> intervals = new ArrayList<>();

            int i = dayStart;

            while (i < dayEnd) {

                if (!translated[i]) {
                    i++;
                    continue;
                }

                int start = i;

                while (i < dayEnd && translated[i]) {
                    i++;
                }

                int end = i - dayStart;

                // If availability reaches midnight,
                // output 00:00 as the end time.
                if (i == dayEnd) {
                    end = DAY;
                }

                intervals.add(new int[]{
                    start - dayStart,
                    end
                });
            }

            ans.append(intervals.size()).append('\n');

            for (int[] interval : intervals) {
                ans.append(toTime(interval[0]))
                   .append(' ')
                   .append(toTime(interval[1]))
                   .append('\n');
            }
        }

        System.out.print(ans);

        sc.close();
    }
}