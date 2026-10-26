import java.io.*;

public class Main {
    static final long DAY = 86400L;

    static boolean matches(String p, int x) {
        char a = (char) ('0' + x / 10);
        char b = (char) ('0' + x % 10);

        return (p.charAt(0) == '?' || p.charAt(0) == a)
            && (p.charAt(1) == '?' || p.charAt(1) == b);
    }

    static int[] getValues(String p, int limit) {
        int[] temp = new int[limit];
        int count = 0;

        for (int i = 0; i < limit; i++) {
            if (matches(p, i)) {
                temp[count++] = i;
            }
        }

        int[] result = new int[count];
        System.arraycopy(temp, 0, result, 0, count);
        return result;
    }

    // Returns the earliest valid time >= lower, or -1 if none exists.
    static int nextTime(String s, int lower) {
        String hp = s.substring(0, 2);
        String mp = s.substring(3, 5);
        String sp = s.substring(6, 8);

        int[] hours = getValues(hp, 24);
        int[] minutes = getValues(mp, 60);
        int[] seconds = getValues(sp, 60);

        int th = lower / 3600;
        int tm = (lower / 60) % 60;
        int ts = lower % 60;

        for (int h : hours) {
            if (h < th) continue;

            if (h > th) {
                return h * 3600 + minutes[0] * 60 + seconds[0];
            }

            for (int m : minutes) {
                if (m < tm) continue;

                if (m > tm) {
                    return h * 3600 + m * 60 + seconds[0];
                }

                for (int sec : seconds) {
                    if (sec >= ts) {
                        return h * 3600 + m * 60 + sec;
                    }
                }
            }
        }

        return -1;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );

        int t = Integer.parseInt(br.readLine().trim());
        StringBuilder out = new StringBuilder();

        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine().trim());
            long elapsed = 0;

            for (int i = 0; i < n; i++) {
                String s = br.readLine().trim();

                int lower = (int) (elapsed % DAY);
                int time = nextTime(s, lower);

                if (time == -1) {
                    elapsed = (elapsed / DAY + 1) * DAY;
                    time = nextTime(s, 0);
                } else {
                    elapsed = (elapsed / DAY) * DAY;
                }

                elapsed += time;
            }

            out.append(elapsed).append('\n');
        }

        System.out.print(out);
    }
}