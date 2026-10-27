import java.util.*;

class Solution {
    public char nthCharacter(int n) {
        long digits = 9;
        long start = 1;
        int length = 1;

        while (n > digits * length) {
            n -= digits * length;
            digits *= 10;
            start *= 10;
            length++;
        }

        long number = start + (n - 1) / length;
        int index = (n - 1) % length;

        return Long.toString(number).charAt(index);
    }
}