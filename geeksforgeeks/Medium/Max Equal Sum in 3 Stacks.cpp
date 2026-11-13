import java.util.ArrayList;

class Solution {
    public static int maxEqualSum(ArrayList<Integer> s1, ArrayList<Integer> s2, ArrayList<Integer> s3) {
        long sum1 = 0, sum2 = 0, sum3 = 0;
        
        // Calculate initial sums for all three stacks
        for (int x : s1) sum1 += x;
        for (int x : s2) sum2 += x;
        for (int x : s3) sum3 += x;
        
        int i1 = 0, i2 = 0, i3 = 0;
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        
        while (i1 < n1 && i2 < n2 && i3 < n3) {
            // Check if all sums are equal
            if (sum1 == sum2 && sum2 == sum3) {
                return (int) sum1;
            }
            
            // Reduce the stack with the maximum sum
            if (sum1 >= sum2 && sum1 >= sum3) {
                sum1 -= s1.get(i1++);
            } else if (sum2 >= sum1 && sum2 >= sum3) {
                sum2 -= s2.get(i2++);
            } else {
                sum3 -= s3.get(i3++);
            }
        }
        
        // Final check after loop in case equality is reached at the boundary
        if (sum1 == sum2 && sum2 == sum3) {
            return (int) sum1;
        }
        
        return 0;
    }
}