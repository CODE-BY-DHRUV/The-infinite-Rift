import java.util.*;

class Solution {

    static int[] tree;

    static int gcd(int a, int b) {
        while (b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    static void build(int[] arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;

        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);

        tree[node] = gcd(tree[2 * node], tree[2 * node + 1]);
    }

    static void update(int node, int start, int end,
                       int index, int value) {

        if (start == end) {
            tree[node] = value;
            return;
        }

        int mid = (start + end) / 2;

        if (index <= mid) {
            update(2 * node, start, mid, index, value);
        } else {
            update(2 * node + 1, mid + 1, end, index, value);
        }

        tree[node] = gcd(tree[2 * node], tree[2 * node + 1]);
    }

    static int query(int node, int start, int end,
                     int l, int r) {

        // No overlap
        if (r < start || end < l) {
            return 0;
        }

        // Complete overlap
        if (l <= start && end <= r) {
            return tree[node];
        }

        int mid = (start + end) / 2;

        int left = query(2 * node, start, mid, l, r);
        int right = query(2 * node + 1, mid + 1, end, l, r);

        return gcd(left, right);
    }

    // IMPORTANT: GFG driver expects this exact method name
    public ArrayList<Integer> processQueries(int[] arr, int[][] queries) {

        int n = arr.length;

        tree = new int[4 * n];

        build(arr, 1, 0, n - 1);

        ArrayList<Integer> answers = new ArrayList<>();

        for (int[] q : queries) {

            if (q[0] == 0) {
                // Type 0: [0, l, r]
                int l = q[1];
                int r = q[2];

                answers.add(query(1, 0, n - 1, l, r));

            } else {
                // Type 1: [1, index, value]
                int index = q[1];
                int value = q[2];

                update(1, 0, n - 1, index, value);
            }
        }

        return answers;
    }
}