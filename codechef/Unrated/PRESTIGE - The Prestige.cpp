import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) {
                    return -1;
                }
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c;

            do {
                c = read();
            } while (c <= ' ');

            int sign = 1;

            if (c == '-') {
                sign = -1;
                c = read();
            }

            int res = 0;

            while (c > ' ') {
                res = res * 10 + (c - '0');
                c = read();
            }

            return res * sign;
        }
    }

    static class Node {
        Node left;
        Node right;

        int priority;
        int size;

        long top;
        long bottom;

        long sumTop;
        long sumBottom;

        boolean rev;

        Node(long top, long bottom, int priority) {
            this.top = top;
            this.bottom = bottom;

            this.sumTop = top;
            this.sumBottom = bottom;

            this.priority = priority;
            this.size = 1;
        }
    }

    static final Random RNG = new Random(123456789);

    static int size(Node root) {
        return root == null ? 0 : root.size;
    }

    static long sumTop(Node root) {
        return root == null ? 0L : root.sumTop;
    }

    static long sumBottom(Node root) {
        return root == null ? 0L : root.sumBottom;
    }

    static void update(Node root) {
        if (root == null) {
            return;
        }

        root.size = 1 + size(root.left) + size(root.right);

        root.sumTop =
                root.top
                + sumTop(root.left)
                + sumTop(root.right);

        root.sumBottom =
                root.bottom
                + sumBottom(root.left)
                + sumBottom(root.right);
    }

    static void applyReverse(Node root) {
        if (root == null) {
            return;
        }

        root.rev ^= true;

        Node temp = root.left;
        root.left = root.right;
        root.right = temp;

        long value = root.top;
        root.top = root.bottom;
        root.bottom = value;

        value = root.sumTop;
        root.sumTop = root.sumBottom;
        root.sumBottom = value;
    }

    static void push(Node root) {
        if (root == null || !root.rev) {
            return;
        }

        applyReverse(root.left);
        applyReverse(root.right);

        root.rev = false;
    }

    static Node[] split(Node root, int k) {
        if (root == null) {
            return new Node[]{null, null};
        }

        push(root);

        int leftSize = size(root.left);

        if (k <= leftSize) {

            Node[] result = split(root.left, k);

            root.left = result[1];

            update(root);

            return new Node[]{result[0], root};

        } else {

            Node[] result =
                    split(root.right, k - leftSize - 1);

            root.right = result[0];

            update(root);

            return new Node[]{root, result[1]};
        }
    }

    static Node merge(Node a, Node b) {
        if (a == null) {
            return b;
        }

        if (b == null) {
            return a;
        }

        if (a.priority > b.priority) {

            push(a);

            a.right = merge(a.right, b);

            update(a);

            return a;

        } else {

            push(b);

            b.left = merge(a, b.left);

            update(b);

            return b;
        }
    }

    static Node append(Node root, long top, long bottom) {
        Node node =
                new Node(top, bottom, RNG.nextInt());

        return merge(root, node);
    }

    static Node reverseRange(Node root, int l, int r) {

        Node[] first = split(root, l - 1);

        Node left = first[0];
        Node rest = first[1];

        Node[] second =
                split(rest, r - l + 1);

        Node middle = second[0];
        Node right = second[1];

        applyReverse(middle);

        root = merge(left, middle);
        root = merge(root, right);

        return root;
    }

    static class QueryResult {
        Node root;
        long sum;

        QueryResult(Node root, long sum) {
            this.root = root;
            this.sum = sum;
        }
    }

    static QueryResult rangeTopSum(Node root, int l, int r) {

        if (l > r) {
            return new QueryResult(root, 0L);
        }

        Node[] first =
                split(root, l - 1);

        Node left = first[0];
        Node rest = first[1];

        Node[] second =
                split(rest, r - l + 1);

        Node middle = second[0];
        Node right = second[1];

        long answer = sumTop(middle);

        root = merge(left, middle);
        root = merge(root, right);

        return new QueryResult(root, answer);
    }

    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();

        StringBuilder out =
                new StringBuilder();

        int n = fs.nextInt();
        int m = fs.nextInt();

        long[] top =
                new long[n + 1];

        long[] bottom =
                new long[n + 1];

        for (int i = 1; i <= n; i++) {
            top[i] = fs.nextInt();
        }

        for (int i = 1; i <= n; i++) {
            bottom[i] = fs.nextInt();
        }

        Node root = null;

        for (int i = 1; i <= n; i++) {
            root =
                    append(root, top[i], bottom[i]);
        }

        int K = 0;

        while (m-- > 0) {

            int type = fs.nextInt();

            if (type == 1) {

                int L = fs.nextInt();
                int R = fs.nextInt();

                root =
                        reverseRange(root, L, R);

            } else if (type == 2) {

                int x = fs.nextInt();

                K = x - K;

            } else {

                int A = fs.nextInt();
                int B = fs.nextInt();
                int C = fs.nextInt();
                int D = fs.nextInt();

                int negativeCount = 0;

                if (C <= K) {
                    negativeCount =
                            Math.min(D, K) - C + 1;
                }

                QueryResult whole =
                        rangeTopSum(root, A, B);

                root = whole.root;

                long answer =
                        whole.sum;

                if (negativeCount > 0) {

                    int negL = A;
                    int negR =
                            A + negativeCount - 1;

                    QueryResult negativePart =
                            rangeTopSum(
                                    root,
                                    negL,
                                    negR
                            );

                    root =
                            negativePart.root;

                    answer -=
                            2L * negativePart.sum;
                }

                out.append(answer)
                    .append('\n');
            }
        }

        System.out.print(out);
    }
}