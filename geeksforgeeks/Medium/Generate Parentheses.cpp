class Solution {

    public ArrayList<String> generateParentheses(int n) {
        ArrayList<String> ans = new ArrayList<>();

        StringBuilder current = new StringBuilder();

        solve(n, 0, 0, current, ans);

        return ans;
    }

    void solve(int n, int open, int close,
               StringBuilder current,
               ArrayList<String> ans) {

        // Complete valid sequence
        if (current.length() == n) {
            ans.add(current.toString());
            return;
        }

        // Add opening bracket
        if (open < n / 2) {
            current.append('(');

            solve(n, open + 1, close, current, ans);

            current.deleteCharAt(current.length() - 1);
        }

        // Add closing bracket only when valid
        if (close < open) {
            current.append(')');

            solve(n, open, close + 1, current, ans);

            current.deleteCharAt(current.length() - 1);
        }
    }
}