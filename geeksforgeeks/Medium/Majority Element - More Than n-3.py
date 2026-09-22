import java.util.*;

class Solution {
    public ArrayList<Integer> findMajority(int[] arr) {
        int n = arr.length;

        // Two possible candidates
        int cand1 = 0, cand2 = 1;
        int count1 = 0, count2 = 0;

        // Step 1: Find possible candidates
        for (int num : arr) {
            if (num == cand1) {
                count1++;
            } 
            else if (num == cand2) {
                count2++;
            } 
            else if (count1 == 0) {
                cand1 = num;
                count1 = 1;
            } 
            else if (count2 == 0) {
                cand2 = num;
                count2 = 1;
            } 
            else {
                count1--;
                count2--;
            }
        }

        // Step 2: Verify the candidates
        count1 = 0;
        count2 = 0;

        for (int num : arr) {
            if (num == cand1) {
                count1++;
            }
            if (num == cand2) {
                count2++;
            }
        }

        ArrayList<Integer> ans = new ArrayList<>();

        if (count1 > n / 3) {
            ans.add(cand1);
        }

        // cand2 must be different from cand1
        if (cand2 != cand1 && count2 > n / 3) {
            ans.add(cand2);
        }

        // Required: strictly increasing order
        Collections.sort(ans);

        return ans;
    }
}