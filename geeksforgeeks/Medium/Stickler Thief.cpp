class Solution {
    public int findMaxSum(int arr[]) {
        int prev2 = 0; // Maximum loot up to i-2
        int prev1 = 0; // Maximum loot up to i-1

        for (int money : arr) {
            int take = prev2 + money;
            int skip = prev1;

            int current = Math.max(take, skip);

            prev2 = prev1;
            prev1 = current;
        }

        return prev1;
    }
}