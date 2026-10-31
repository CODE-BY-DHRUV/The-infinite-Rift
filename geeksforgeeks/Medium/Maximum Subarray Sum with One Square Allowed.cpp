

class Solution {
    public int maximumSubarray(int[] arr) {
        int noSquare = arr[0];
        int oneSquare = arr[0] * arr[0];

        int ans = Math.max(noSquare, oneSquare);

        for (int i = 1; i < arr.length; i++) {
            int x = arr[i];

            int newOneSquare = Math.max(
                x * x,
                Math.max(
                    noSquare + x * x,
                    oneSquare + x
                )
            );

            int newNoSquare = Math.max(
                x,
                noSquare + x
            );

            noSquare = newNoSquare;
            oneSquare = newOneSquare;

            ans = Math.max(ans,
                Math.max(noSquare, oneSquare));
        }

        return ans;
    }
}

