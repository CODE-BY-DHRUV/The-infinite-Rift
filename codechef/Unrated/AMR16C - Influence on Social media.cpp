import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.Arrays;

public class Main {

    static class Person implements Comparable<Person> {
        long posts;
        int rank; // overall influence rank (1-based)

        public Person(long posts) {
            this.posts = posts;
        }

        @Override
        public int compareTo(Person o) {
            // Descending order of posts (most posts = most influence = rank 1)
            return Long.compare(o.posts, this.posts);
        }
    }

    static boolean isSupporter(long x) {
        int[] ks = {2, 4, 6, 10, 12, 16, 18, 22, 28, 30, 36};
        for (int k : ks) {
            double root = Math.pow(x, 1.0 / k);
            long q = Math.round(root);
            for (long testQ = Math.max(2, q - 2); testQ <= q + 2; testQ++) {
                long val = power(testQ, k);
                if (val == x) {
                    if (isPrime(testQ)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    static long power(long base, int exp) {
        long res = 1;
        long b = base;
        for (int i = 0; i < exp; i++) {
            if (Long.MAX_VALUE / b < res) return -1; // overflow
            res *= b;
        }
        return res;
    }

    static boolean isPrime(long n) {
        if (n < 2) return false;
        for (long i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        String line = br.readLine();
        if (line == null) return;
        int T = Integer.parseInt(line.trim());
        StringBuilder sb = new StringBuilder();

        while (T-- > 0) {
            int N = Integer.parseInt(br.readLine().trim());
            Person[] persons = new Person[N];
            
            st = new StringTokenizer(br.readLine());
            for (int i = 0; i < N; i++) {
                long p = Long.parseLong(st.nextToken());
                persons[i] = new Person(p);
            }

            // Sort by posts descending
            Arrays.sort(persons);

            // Assign ranks (1-based)
            for (int i = 0; i < N; i++) {
                persons[i].rank = i + 1;
            }

            StringBuilder supporterRanks = new StringBuilder();
            int supporterCount = 0;

            for (int i = 0; i < N; i++) {
                if (isSupporter(persons[i].posts)) {
                    supporterCount++;
                    if (supporterCount > 1) {
                        supporterRanks.append(" ");
                    }
                    supporterRanks.append(persons[i].rank);
                }
            }

            if (supporterCount == 0) {
                sb.append("No supporter found.\n");
            } else {
                sb.append(supporterRanks).append("\n");
            }
        }
        System.out.print(sb);
    }
}