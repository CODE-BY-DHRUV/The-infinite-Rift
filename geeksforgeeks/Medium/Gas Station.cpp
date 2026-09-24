class Solution {
    public int startStation(int[] gas, int[] cost) {
        int n = gas.length;

        int totalGas = 0;
        int totalCost = 0;

        int tank = 0;
        int start = 0;

        for (int i = 0; i < n; i++) {
            totalGas += gas[i];
            totalCost += cost[i];

            tank += gas[i] - cost[i];

            // Current starting point cannot work
            if (tank < 0) {
                start = i + 1;
                tank = 0;
            }
        }

        // Not enough gas overall
        if (totalGas < totalCost) {
            return -1;
        }

        return start;
    }
}