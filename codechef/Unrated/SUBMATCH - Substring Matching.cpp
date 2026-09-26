import java.io.*;
import java.util.*;

public class Main {

    // ------------------------------------------------------------
    // Fast Scanner
    // ------------------------------------------------------------

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        String next() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            StringBuilder sb = new StringBuilder();

            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }

            return sb.toString();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    // ------------------------------------------------------------
    // Fast Long -> Integer hash map
    // ------------------------------------------------------------

    /*
     * We only need:
     *
     * hash -> number of copies of this string
     *
     * value 0 means the key does not exist.
     */
    static class LongIntMap {
        long[] keys;
        int[] values;
        int mask;

        LongIntMap(int expectedSize) {
            int size = 1;

            while (size < expectedSize * 2) {
                size <<= 1;
            }

            keys = new long[size];
            values = new int[size];
            mask = size - 1;
        }

        private int index(long x) {
            x ^= (x >>> 33);
            x *= 0xff51afd7ed558ccdL;
            x ^= (x >>> 33);
            x *= 0xc4ceb9fe1a85ec53L;
            x ^= (x >>> 33);

            return ((int) x) & mask;
        }

        void add(long key) {
            int pos = index(key);

            while (values[pos] != 0) {
                if (keys[pos] == key) {
                    values[pos]++;
                    return;
                }

                pos = (pos + 1) & mask;
            }

            keys[pos] = key;
            values[pos] = 1;
        }

        int get(long key) {
            int pos = index(key);

            while (values[pos] != 0) {
                if (keys[pos] == key) {
                    return values[pos];
                }

                pos = (pos + 1) & mask;
            }

            return 0;
        }
    }

    // ------------------------------------------------------------
    // Rolling hash
    // ------------------------------------------------------------

    /*
     * 64-bit polynomial hash.
     *
     * Arithmetic intentionally overflows long, effectively working
     * modulo 2^64.
     */
    static final long HASH_BASE = 911382323L;

    static long[] pref;
    static long[] power;

    static void buildHash(String s) {
        int n = s.length();

        pref = new long[n + 1];
        power = new long[n + 1];

        power[0] = 1;

        for (int i = 0; i < n; i++) {
            power[i + 1] =
                    power[i] * HASH_BASE;

            pref[i + 1] =
                    pref[i] * HASH_BASE
                    + (s.charAt(i) - 'a' + 1);
        }
    }

    /*
     * Hash of T[l ... l+len-1]
     */
    static long getHash(int l, int len) {
        return pref[l + len]
                - pref[l] * power[len];
    }

    static long hashString(String s) {
        long h = 0;

        for (int i = 0; i < s.length(); i++) {
            h = h * HASH_BASE
                    + (s.charAt(i) - 'a' + 1);
        }

        return h;
    }

    // ------------------------------------------------------------
    // Main solver
    // ------------------------------------------------------------

    static int solve(String T, String[] words) {

        int m = T.length();

        /*
         * Sort by length.
         */
        Arrays.sort(words, new Comparator<String>() {
            @Override
            public int compare(String a, String b) {
                return Integer.compare(a.length(), b.length());
            }
        });

        buildHash(T);

        /*
         * dp[p] =
         * maximum length of a valid constructed substring
         * whose ending position is p.
         *
         * Position p means the substring occupies [start, p).
         *
         * dp[p] = 0 is also valid, meaning we can start
         * a new substring at p.
         */
        int[] dp = new int[m + 1];

        int answer = 0;

        int idx = 0;

        while (idx < words.length) {

            int L = words[idx].length();

            /*
             * Find [idx, end) = all strings having length L.
             */
            int end = idx;

            while (end < words.length
                    && words[end].length() == L) {
                end++;
            }

            /*
             * If the strings are longer than T, they can never
             * participate.
             */
            if (L <= m) {

                /*
                 * Count identical strings.
                 *
                 * For example:
                 *
                 * a
                 * a
                 * a
                 *
                 * gives hash("a") -> 3.
                 */
                LongIntMap available =
                        new LongIntMap(end - idx);

                for (int i = idx; i < end; i++) {
                    available.add(
                            hashString(words[i])
                    );
                }

                /*
                 * VERY IMPORTANT:
                 *
                 * All transitions for this length must use
                 * the dp values from before this length was
                 * processed.
                 *
                 * Otherwise a string of length L could be
                 * accidentally used more times than available.
                 */
                int[] base = dp.clone();

                /*
                 * Positions having the same p % L form an
                 * independent sequence of blocks of length L.
                 */
                for (int rem = 0; rem < L; rem++) {

                    /*
                     * Number of complete L-sized blocks on
                     * this residue class.
                     *
                     * block index k corresponds to:
                     *
                     * position = rem + k*L
                     */
                    int blockCount =
                            (m - rem) / L;

                    if (blockCount == 0) {
                        continue;
                    }

                    /*
                     * Sliding window over blocks.
                     *
                     * We need frequency of each string/hash
                     * inside the current window.
                     *
                     * Instead of another HashMap, use the same
                     * custom map.
                     */
                    LongIntMap used =
                            new LongIntMap(
                                    Math.max(1, blockCount)
                            );

                    /*
                     * For every left endpoint 'left', we find
                     * the maximum right endpoint 'right'.
                     *
                     * The corresponding interval is:
                     *
                     * [left, right]
                     *
                     * in block-index coordinates.
                     *
                     * We store:
                     *
                     * value[left] = base[position] - position
                     *
                     * because for any endpoint q:
                     *
                     * base[position]
                     * + (q-position)
                     *
                     * = q + (base[position]-position).
                     *
                     * This turns the transitions into a
                     * sliding-window maximum.
                     */
                    int[] rightEnd =
                            new int[blockCount];

                    long[] value =
                            new long[blockCount];

                    Arrays.fill(
                            rightEnd, -1
                    );

                    int right = -1;

                    for (int left = 0;
                         left < blockCount;
                         left++) {

                        if (right < left - 1) {
                            right = left - 1;
                        }

                        /*
                         * Extend the window.
                         */
                        while (right + 1 < blockCount) {

                            int pos =
                                    rem
                                    + (right + 1) * L;

                            long h =
                                    getHash(pos, L);

                            int limit =
                                    available.get(h);

                            /*
                             * This block is not one of our
                             * strings of length L.
                             */
                            if (limit == 0) {
                                break;
                            }

                            /*
                             * Add this block.
                             */
                            used.add(h);

                            int now =
                                    used.get(h);

                            /*
                             * Too many copies of this string.
                             *
                             * Remove it and stop extending.
                             */
                            if (now > limit) {

                                /*
                                 * We cannot directly decrement
                                 * our map, so instead break and
                                 * reconstruct the window below.
                                 *
                                 * To avoid this complication,
                                 * use a special decrementable map.
                                 */
                                break;
                            }

                            right++;
                        }

                        /*
                         * The above map needs decrement support.
                         *
                         * We handle the group with the more
                         * convenient implementation below.
                         */
                    }
                }
            }

            idx = end;
        }

        return answer;
    }

    // ------------------------------------------------------------
    // A decrementable map for sliding windows
    // ------------------------------------------------------------

    static class CounterMap {
        long[] keys;
        int[] values;
        int mask;

        CounterMap(int expectedSize) {
            int size = 1;

            while (size < expectedSize * 2) {
                size <<= 1;
            }

            keys = new long[size];
            values = new int[size];
            mask = size - 1;
        }

        private int index(long x) {
            x ^= x >>> 33;
            x *= 0xff51afd7ed558ccdL;
            x ^= x >>> 33;
            x *= 0xc4ceb9fe1a85ec53L;
            x ^= x >>> 33;

            return ((int) x) & mask;
        }

        int get(long key) {
            int p = index(key);

            while (values[p] != 0) {
                if (keys[p] == key) {
                    return values[p];
                }

                p = (p + 1) & mask;
            }

            return 0;
        }

        void add(long key) {
            int p = index(key);

            while (values[p] != 0) {
                if (keys[p] == key) {
                    values[p]++;
                    return;
                }

                p = (p + 1) & mask;
            }

            keys[p] = key;
            values[p] = 1;
        }

        void remove(long key) {
            int p = index(key);

            while (values[p] != 0) {
                if (keys[p] == key) {
                    values[p]--;

                    /*
                     * We don't need to physically remove the
                     * key because it may be searched again.
                     */
                    return;
                }

                p = (p + 1) & mask;
            }
        }
    }

    // ------------------------------------------------------------
    // Actual efficient solver
    // ------------------------------------------------------------

    static int solveFast(
            String T,
            String[] words
    ) {

        int m = T.length();

        Arrays.sort(words,
                Comparator.comparingInt(String::length));

        buildHash(T);

        int[] dp = new int[m + 1];

        int answer = 0;

        int idx = 0;

        while (idx < words.length) {

            int L = words[idx].length();

            int end = idx;

            while (end < words.length
                    && words[end].length() == L) {
                end++;
            }

            if (L <= m) {

                /*
                 * Number of different copies available for
                 * each exact string.
                 */
                LongIntMap available =
                        new LongIntMap(end - idx);

                for (int i = idx; i < end; i++) {
                    available.add(
                            hashString(words[i])
                    );
                }

                /*
                 * Snapshot before processing this length.
                 */
                int[] base = dp.clone();

                /*
                 * Process every residue modulo L.
                 */
                for (int rem = 0; rem < L; rem++) {

                    int blocks =
                            (m - rem) / L;

                    if (blocks <= 0) {
                        continue;
                    }

                    /*
                     * For every block we calculate its hash once.
                     */
                    long[] hashes =
                            new long[blocks];

                    for (int k = 0;
                         k < blocks;
                         k++) {

                        int pos =
                                rem + k * L;

                        hashes[k] =
                                getHash(pos, L);
                    }

                    /*
                     * Find the maximum valid right endpoint
                     * for every left endpoint.
                     */
                    int[] rightForLeft =
                            new int[blocks];

                    Arrays.fill(
                            rightForLeft, -1
                    );

                    CounterMap used =
                            new CounterMap(
                                    Math.max(1, blocks)
                            );

                    int right = -1;

                    for (int left = 0;
                         left < blocks;
                         left++) {

                        /*
                         * right can never move backwards.
                         */
                        if (right < left - 1) {
                            right = left - 1;
                        }

                        while (right + 1 < blocks) {

                            long h =
                                    hashes[right + 1];

                            int limit =
                                    available.get(h);

                            /*
                             * Not present in dictionary.
                             */
                            if (limit == 0) {
                                break;
                            }

                            int old =
                                    used.get(h);

                            /*
                             * Adding this block would exceed
                             * the number of available copies.
                             */
                            if (old + 1 > limit) {
                                break;
                            }

                            used.add(h);
                            right++;
                        }

                        rightForLeft[left] = right;

                        /*
                         * Remove the left block before moving
                         * to the next left endpoint.
                         */
                        if (right >= left) {
                            used.remove(
                                    hashes[left]
                            );
                        } else {
                            right = left;
                        }
                    }

                    /*
                     * Now we have intervals:
                     *
                     * left -> rightForLeft[left]
                     *
                     * For every endpoint q, we need:
                     *
                     * max(base[start] - start)
                     *
                     * among intervals containing q.
                     *
                     * Because rightForLeft[left] is
                     * non-decreasing, this becomes a normal
                     * sliding-window maximum.
                     */
                    int[] deque =
                            new int[blocks];

                    int head = 0;
                    int tail = 0;

                    for (int block = 0;
                         block < blocks;
                         block++) {

                        int startPos =
                                rem + block * L;

                        int r =
                                rightForLeft[block];

                        if (r >= block) {

                            long value =
                                    (long) base[startPos]
                                    - startPos;

                            /*
                             * Maintain decreasing values.
                             */
                            while (tail > head) {

                                int last =
                                        deque[tail - 1];

                                int lastPos =
                                        rem + last * L;

                                long lastValue =
                                        (long) base[lastPos]
                                        - lastPos;

                                if (lastValue > value) {
                                    break;
                                }

                                tail--;
                            }

                            deque[tail++] = block;
                        }

                        /*
                         * Remove expired intervals.
                         */
                        while (tail > head
                                && rightForLeft[
                                    deque[head]
                                ] < block) {

                            head++;
                        }

                        if (tail > head) {

                            int bestLeft =
                                    deque[head];

                            int bestStart =
                                    rem
                                    + bestLeft * L;

                            int endPos =
                                    startPos + L;

                            long value =
                                    (long) endPos
                                    + ((long) base[bestStart]
                                    - bestStart);

                            if (value > dp[endPos]) {
                                dp[endPos] =
                                        (int) value;
                            }

                            answer =
                                    Math.max(
                                            answer,
                                            dp[endPos]
                                    );
                        }
                    }
                }
            }

            idx = end;
        }

        return answer;
    }

    // ------------------------------------------------------------
    // Main
    // ------------------------------------------------------------

    public static void main(String[] args)
            throws Exception {

        FastScanner fs =
                new FastScanner();

        StringBuilder out =
                new StringBuilder();

        int Q = fs.nextInt();

        while (Q-- > 0) {

            String T = fs.next();

            int n = fs.nextInt();

            String[] words =
                    new String[n];

            for (int i = 0; i < n; i++) {
                words[i] = fs.next();
            }

            out.append(
                    solveFast(T, words)
            ).append('\n');
        }

        System.out.print(out);
    }
}