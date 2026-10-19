import java.io.InputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
    static final int MAX_PRIME_INDEX = 3000000;
    static int[] primes = new int[MAX_PRIME_INDEX + 1];

    // Fast Sieve
    static void generatePrimes() {
        int limit = 50000000; 
        byte[] isComposite = new byte[(limit >> 3) + 1];

        int count = 0;
        for (int p = 2; p < limit && count < MAX_PRIME_INDEX; p++) {
            if ((isComposite[p >> 3] & (1 << (p & 7))) == 0) {
                count++;
                primes[count] = p;
                if ((long) p * p < limit) {
                    for (int j = p * p; j < limit; j += p) {
                        isComposite[j >> 3] |= (1 << (j & 7));
                    }
                }
            }
        }
    }

    // Legendre's formula
    static long getExponent(long n, long p) {
        long count = 0;
        while (n > 0) {
            count += n / p;
            n /= p;
        }
        return count;
    }

    // Binary search for smallest n such that E_p(n) = t
    static long findL(long p, long t) {
        // Lower bound: n >= t * (p - 1)
        long low = t * (p - 1);
        if (low < 0) low = 0; // overflow safety
        long high = t * p;

        long ans = -1;

        while (low <= high) {
            long mid = low + (high - low) / 2;
            long exp = getExponent(mid, p);

            if (exp >= t) {
                if (exp == t) {
                    ans = mid;
                }
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return ans;
    }

    static class Interval implements Comparable<Interval> {
        long start, end;

        Interval(long start, long end) {
            this.start = start;
            this.end = end;
        }

        @Override
        public int compareTo(Interval o) {
            return Long.compare(this.start, o.start);
        }
    }

    public static void main(String[] args) throws IOException {
        generatePrimes();

        FastScanner sc = new FastScanner();
        Long C_obj = sc.nextLong();
        if (C_obj == null) return;
        long C = C_obj;

        StringBuilder sb = new StringBuilder();

        while (C-- > 0) {
            long low = sc.nextLong();
            long high = sc.nextLong();
            int plow = sc.nextInt();
            int phigh = sc.nextInt();
            long t = sc.nextLong();

            List<Interval> intervals = new ArrayList<>();

            for (int i = plow; i <= phigh; i++) {
                long p = primes[i];

                // Pruning: if lowest possible n for prime p exceeds high, stop early
                if (t > 0 && p - 1 > high / t) {
                    break;
                }

                long L = findL(p, t);
                
                if (L != -1 && L <= high) {
                    long R = L + p - 1;
                    
                    long start = Math.max(L, low);
                    long end = Math.min(R, high);

                    if (start <= end) {
                        intervals.add(new Interval(start, end));
                    }
                }
            }

            if (intervals.isEmpty()) {
                sb.append(0).append("\n");
                continue;
            }

            Collections.sort(intervals);

            long totalCount = 0;
            long curStart = intervals.get(0).start;
            long curEnd = intervals.get(0).end;

            for (int i = 1; i < intervals.size(); i++) {
                Interval next = intervals.get(i);
                if (next.start <= curEnd + 1) {
                    curEnd = Math.max(curEnd, next.end);
                } else {
                    totalCount += (curEnd - curStart + 1);
                    curStart = next.start;
                    curEnd = next.end;
                }
            }
            totalCount += (curEnd - curStart + 1);

            sb.append(totalCount).append("\n");
        }

        System.out.print(sb);
    }

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[65536];
        private int ptr = 0;
        private int buflen = 0;

        private boolean hasNextByte() {
            if (ptr < buflen) return true;
            ptr = 0;
            try {
                buflen = in.read(buffer, 0, buffer.length);
            } catch (IOException e) {
                e.printStackTrace();
            }
            return buflen > 0;
        }

        private int readByte() {
            if (hasNextByte()) return buffer[ptr++];
            return -1;
        }

        public Integer nextInt() {
            Long nl = nextLong();
            if (nl == null) return null;
            return nl.intValue();
        }

        public Long nextLong() {
            int b = readByte();
            while (b <= 32 && b != -1) b = readByte();
            if (b == -1) return null;
            boolean minus = false;
            if (b == '-') {
                minus = true;
                b = readByte();
            }
            long num = 0;
            while (b >= '0' && b <= '9') {
                num = num * 10 + (b - '0');
                b = readByte();
            }
            return minus ? -num : num;
        }
    }
}