class Solution {
    public int firstElementKTime(int[] arr, int k) {
        // Find max element to size the frequency array, or use a fixed size 1000001
        int[] freq = new int[1000001];

        for (int num : arr) {
            freq[num]++;
            if (freq[num] == k) {
                return num;
            }
        }

        return -1;
    }
}