
import java.io.*;
import java.util.*;

public class Main {
    static class Key {
        int[] children;
        int hash;

        Key(int[] children) {
            this.children = children;
            hash = Arrays.hashCode(children);
        }

        public int hashCode() {
            return hash;
        }

        public boolean equals(Object obj) {
            if (this == obj) return true;
            if (!(obj instanceof Key)) return false;
            return Arrays.equals(children, ((Key) obj).children);
        }
    }

    static HashMap<Key, Integer> ids;
    static int nextId;

    static int getId(int[] children) {
        Key key = new Key(children);
        Integer existing = ids.get(key);

        if (existing != null) return existing;

        int id = nextId++;
        ids.put(key, id);
        return id;
    }

    static class Result {
        int[] type;
        long[] leafOrbits;
        HashSet<Integer> distinctTypes;

        Result(int[] type, long[] leafOrbits,
               HashSet<Integer> distinctTypes) {
            this.type = type;
            this.leafOrbits = leafOrbits;
            this.distinctTypes = distinctTypes;
        }
    }

    static Result process(int n, int[] first, int[] next,
                          boolean countOrbits, long[] orbitByType) {
        int[] type = new int[n + 1];
        long[] leafOrbits = new long[n + 1];
        HashSet<Integer> distinctTypes = new HashSet<>();

        for (int u = n; u >= 1; u--) {
            int degree = 0;
            for (int v = first[u]; v != 0; v = next[v]) {
                degree++;
            }

            int[] children = new int[degree];
            int p = 0;

            for (int v = first[u]; v != 0; v = next[v]) {
                children[p++] = type[v];
            }

            Arrays.sort(children);
            type[u] = getId(children);
            distinctTypes.add(type[u]);

            if (countOrbits) {
                if (degree == 0) {
                    leafOrbits[u] = 1;
                } else {
                    long count = 0;

                    for (int i = 0; i < degree; ) {
                        int childType = children[i];
                        count += orbitByType[childType];

                        while (i < degree &&
                               children[i] == childType) {
                            i++;
                        }
                    }

                    leafOrbits[u] = count;
                }

                orbitByType[type[u]] = leafOrbits[u];
            }
        }

        return new Result(type, leafOrbits, distinctTypes);
    }

    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();

        while (t-- > 0) {
            int n1 = fs.nextInt();
            int n2 = fs.nextInt();

            int[] first1 = new int[n1 + 1];
            int[] next1 = new int[n1 + 1];
            int[] first2 = new int[n2 + 1];
            int[] next2 = new int[n2 + 1];

            for (int i = 2; i <= n1; i++) {
                int parent = fs.nextInt();
                next1[i] = first1[parent];
                first1[parent] = i;
            }

            for (int i = 2; i <= n2; i++) {
                int parent = fs.nextInt();
                next2[i] = first2[parent];
                first2[parent] = i;
            }

            ids = new HashMap<>();
            nextId = 1;

            long[] orbitByType = new long[n1 + n2 + 5];

            Result tree1 = process(
                n1, first1, next1, true, orbitByType
            );

            Result tree2 = process(
                n2, first2, next2, false, orbitByType
            );

            long answer =
                tree1.leafOrbits[1] * tree2.distinctTypes.size();

            out.append(answer).append('\n');
        }

        System.out.print(out);
    }

    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr, len;

        FastScanner(InputStream in) {
            this.in = in;
        }

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);

            int value = 0;
            while (c > ' ') {
                value = value * 10 + c - '0';
                c = read();
            }
            return value;
        }
    }
}

