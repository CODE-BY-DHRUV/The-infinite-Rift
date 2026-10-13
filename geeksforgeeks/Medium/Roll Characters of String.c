
class Solution {
    public String findRollOut(String s, int[] roll) {
        char[] arr = s.toCharArray();
        int n = s.length();

        int shift = 0;

        for (int i = roll.length - 1; i >= 0; i--) {
            shift = (shift + 1) % 26;
            int pos = roll[i] - 1;

            // Store the cumulative shift for this prefix endpoint
            arr[pos] = (char) ('a' + (arr[pos] - 'a'));
        }

        int[] diff = new int[n + 1];

        for (int x : roll) {
            diff[0]++;
            diff[x]--;
        }

        int current = 0;

        for (int i = 0; i < n; i++) {
            current += diff[i];
            current %= 26;
            if (current < 0) {
                current += 26;
            }

            arr[i] = (char) ('a' + (s.charAt(i) - 'a' + current) % 26);
        }

        return new String(arr);
    }
}

