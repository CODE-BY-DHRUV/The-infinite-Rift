class Solution {

    public String decodedString(String s) {

        java.util.Stack<Integer> countStack = new java.util.Stack<>();
        java.util.Stack<StringBuilder> stringStack = new java.util.Stack<>();

        StringBuilder current = new StringBuilder();
        int number = 0;

        for (int i = 0; i < s.length(); i++) {

            char ch = s.charAt(i);

            // Build the number k
            if (Character.isDigit(ch)) {
                number = number * 10 + (ch - '0');
            }

            // Start of a new encoded substring
            else if (ch == '[') {
                countStack.push(number);
                stringStack.push(current);

                number = 0;
                current = new StringBuilder();
            }

            // Normal character
            else if (ch != ']') {
                current.append(ch);
            }

            // End of encoded substring
            else {
                int repeat = countStack.pop();
                StringBuilder previous = stringStack.pop();

                for (int j = 0; j < repeat; j++) {
                    previous.append(current);
                }

                current = previous;
            }
        }

        return current.toString();
    }
}