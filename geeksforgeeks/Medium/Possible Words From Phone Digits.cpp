class Solution {

    ArrayList<String> result = new ArrayList<>();

    String[] keypad = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    public ArrayList<String> possibleWords(int[] arr) {
        result.clear();

        backtrack(arr, 0, new StringBuilder());

        return result;
    }

    private void backtrack(int[] arr, int index, StringBuilder current) {

        // All digits processed
        if (index == arr.length) {
            if (current.length() > 0) {
                result.add(current.toString());
            }
            return;
        }

        int digit = arr[index];

        // 0 and 1 don't contribute letters
        if (digit == 0 || digit == 1) {
            backtrack(arr, index + 1, current);
            return;
        }

        String letters = keypad[digit];

        for (int i = 0; i < letters.length(); i++) {
            current.append(letters.charAt(i));

            backtrack(arr, index + 1, current);

            // Backtrack
            current.deleteCharAt(current.length() - 1);
        }
    }
}