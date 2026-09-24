class Solution {

    public int solve(int x, int y, String s) {

        // Make "pr" the more profitable pair.
        // If "rp" is more profitable, swap p and r.
        if (x < y) {
            int temp = x;
            x = y;
            y = temp;

            StringBuilder converted = new StringBuilder();

            for (char c : s.toCharArray()) {
                if (c == 'p') {
                    converted.append('r');
                } else if (c == 'r') {
                    converted.append('p');
                } else {
                    converted.append(c);
                }
            }

            s = converted.toString();
        }

        int score = 0;

        // First remove the more profitable "pr".
        StringBuilder stack = new StringBuilder();

        for (char c : s.toCharArray()) {

            if (stack.length() > 0 &&
                stack.charAt(stack.length() - 1) == 'p' &&
                c == 'r') {

                stack.deleteCharAt(stack.length() - 1);
                score += x;

            } else {
                stack.append(c);
            }
        }

        // Now remove the less profitable "rp".
        StringBuilder stack2 = new StringBuilder();

        for (int i = 0; i < stack.length(); i++) {

            char c = stack.charAt(i);

            if (stack2.length() > 0 &&
                stack2.charAt(stack2.length() - 1) == 'r' &&
                c == 'p') {

                stack2.deleteCharAt(stack2.length() - 1);
                score += y;

            } else {
                stack2.append(c);
            }
        }

        return score;
    }
}