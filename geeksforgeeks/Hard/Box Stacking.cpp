import java.util.*;

class Solution {

    static class Box {
        int h, w, l;

        Box(int h, int w, int l) {
            this.h = h;
            this.w = w;
            this.l = l;
        }
    }

    public int maxHeight(int[] height, int[] width, int[] length) {
        int n = height.length;

        // Generate all 3 rotations of every box.
        // For the base, always store the larger dimension first.
        List<Box> boxes = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            int h = height[i];
            int w = width[i];
            int l = length[i];

            // h is height, w x l is base
            addBox(boxes, h, w, l);

            // w is height, h x l is base
            addBox(boxes, w, h, l);

            // l is height, h x w is base
            addBox(boxes, l, h, w);
        }

        int m = boxes.size();

        /*
         * dp[i] = maximum height of a stack whose bottom box
         * is rotation i.
         *
         * Since the same box can be used multiple times,
         * transitions are allowed even from a state to the
         * same rotation type again, provided the base becomes
         * strictly smaller.
         */
        int[] dp = new int[m];

        int answer = 0;

        /*
         * Because every transition strictly decreases both base
         * dimensions, cycles are impossible.
         *
         * Sort by base area in decreasing order so that larger
         * bases are processed before smaller bases.
         */
        Collections.sort(boxes, new Comparator<Box>() {
            public int compare(Box a, Box b) {
                long areaA = (long) a.w * a.l;
                long areaB = (long) b.w * b.l;

                return Long.compare(areaB, areaA);
            }
        });

        for (int i = m - 1; i >= 0; i--) {
            Box current = boxes.get(i);

            dp[i] = current.h;

            for (int j = i + 1; j < m; j++) {
                Box above = boxes.get(j);

                // above box must have strictly smaller base
                if (above.w < current.w && above.l < current.l) {
                    dp[i] = Math.max(dp[i], current.h + dp[j]);
                }
            }

            answer = Math.max(answer, dp[i]);
        }

        return answer;
    }

    // Store base dimensions as larger x smaller.
    static void addBox(List<Box> boxes, int h, int w, int l) {
        if (w >= l) {
            boxes.add(new Box(h, w, l));
        } else {
            boxes.add(new Box(h, l, w));
        }
    }
}