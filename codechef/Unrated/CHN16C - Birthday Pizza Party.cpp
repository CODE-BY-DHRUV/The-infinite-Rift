import java.io.*;
import java.util.*;

public class Main {
    // Extended Euclidean Algorithm to solve ax + by = gcd(a, b)
    static long[] extGCD(long a, long b) {
        long x0 = 1, y0 = 0, x1 = 0, y1 = 1;
        while (b != 0) {
            long q = a / b;
            long temp = b;
            b = a % b;
            a = temp;
            
            temp = x1;
            x1 = x0 - q * x1;
            x0 = temp;
            
            temp = y1;
            y1 = y0 - q * y1;
            y0 = temp;
        }
        return new long[]{x0, y0, a}; // returns {x, y, gcd}
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        
        String line = br.readLine();
        if (line == null || line.trim().isEmpty()) return;
        int T = Integer.parseInt(line.trim());
        
        StringBuilder out = new StringBuilder();
        
        while (T-- > 0) {
            line = br.readLine();
            while (line != null && line.trim().isEmpty()) {
                line = br.readLine();
            }
            if (line == null) break;
            st = new StringTokenizer(line);
            long A = Long.parseLong(st.nextToken());
            long N = Long.parseLong(st.nextToken());
            
            // We need to solve A * P ≡ 1 (mod N)
            long[] res = extGCD(A, N);
            long g = res[2];
            
            if (g != 1) {
                out.append(-1).append("\n");
            } else {
                long x = res[0];
                long P = (x % N + N) % N;
                if (P == 0) {
                    P = N;
                }
                out.append(P).append("\n");
            }
        }
        System.out.print(out);
    }
}