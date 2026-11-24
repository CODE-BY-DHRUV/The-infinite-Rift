
class Solution {

    static final long MOD = 1_000_000_007L;

    // Time required to reach position x normally
    private long getTime(long x, long a, long b) {
        long c = a - b;

        long k = 0;

        if (x > a) {
            k = (x - a + c - 1) / c;
        }

        return x + 2L * b * k;
    }

    // Sum of ceil(i / c) for i = 1 to n
    private long prefix(long n, long c) {

        if (n <= 0) return 0;

        long q = n / c;
        long rem = n % c;

        return (c * q % MOD * ((q + 1) % MOD) % MOD
                * 500000004L % MOD
                + (q + 1) % MOD * rem % MOD) % MOD;
    }

    // Sum of ceil((x-a)/c) for x = L to R, where L > a
    private long sumCycles(long L, long R, long a, long c) {

        long left = L - a;
        long right = R - a;

        return (prefix(right, c) - prefix(left - 1, c) + MOD) % MOD;
    }

    // Sum of F(x) for L <= x <= R
    private long sumNormal(long L, long R, long a, long b) {

        if (L > R) return 0;

        long c = a - b;

        long count = R - L + 1;

        long sumPositions =
            ((L + R) % MOD) * (count % MOD) % MOD
            * 500000004L % MOD;

        long cycleSum = 0;

        if (R > a) {
            cycleSum = sumCycles(
                Math.max(L, a + 1),
                R,
                a,
                c
            );
        }

        return (sumPositions +
                2L * b % MOD * cycleSum % MOD) % MOD;
    }

    public int minTime(int a, int b, int d, int l, int r) {

        long normalTime = getTime(d, a, b);

        // Positions required before performing the jump:
        // x = d-j
        long L = (long) d - r;
        long R = (long) d - l;

        // Find the largest x for which:
        // 1 + F(x) < normalTime

        long low = L;
        long high = R;
        long best = L - 1;

        while (low <= high) {

            long mid = low + (high - low) / 2;

            if (1L + getTime(mid, a, b) < normalTime) {

                best = mid;
                low = mid + 1;

            } else {

                high = mid - 1;
            }
        }

        // Use special jump for positions L through best.
        long ans = 0;

        if (best >= L) {

            long specialSum = sumNormal(
                L, best, a, b
            );

            long count = best - L + 1;

            // Each special jump requires one extra second.
            ans = (specialSum + count) % MOD;
        }

        // Use normal movement for remaining positions.
        if (best < R) {

            long count = R - best;

            ans = (ans +
                   count % MOD * (normalTime % MOD) % MOD)
                   % MOD;
        }

        return (int) ans;
    }
}
