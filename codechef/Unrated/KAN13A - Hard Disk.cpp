import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.ArrayList;

public class Main {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st = null;

    static String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            String line = br.readLine();
            if (line == null) return null;
            st = new StringTokenizer(line);
        }
        return st.nextToken();
    }

    static class HardDisk {
        String name;
        int[] price; // 1-indexed for months 1 to m
        HardDisk(String name, int m) {
            this.name = name;
            this.price = new int[m + 2];
        }
    }

    static class Choice {
        int nextMonth;
        String modelName;
        Choice(int nextMonth, String modelName) {
            this.nextMonth = nextMonth;
            this.modelName = modelName;
        }
    }

    public static void main(String[] args) throws IOException {
        String setName;
        while ((setName = nextToken()) != null) {
            if (setName.equals("TheEnd")) break;

            int n = Integer.parseInt(nextToken());
            int m = Integer.parseInt(nextToken());

            HardDisk[] disks = new HardDisk[n];
            for (int i = 0; i < n; i++) {
                String name = nextToken();
                disks[i] = new HardDisk(name, m);
                for (int j = 1; j <= m; j++) {
                    disks[i].price[j] = Integer.parseInt(nextToken());
                }
                // Price at m + 1 if needed (not sold if kept till end, but safe fallback)
                disks[i].price[m + 1] = disks[i].price[m];
            }

            // dp[j]: min cost from month j to m (1-indexed, j goes from 1 to m+1)
            long[] dp = new long[m + 2];
            Choice[] choice = new Choice[m + 1];

            for (int j = m; j >= 1; j--) {
                long minCost = Long.MAX_VALUE;
                int bestNextMonth = j;
                String bestModel = "";

                for (int i = 0; i < n; i++) {
                    for (int e = j; e <= m; e++) {
                        long periodCost;
                        if (e == m) {
                            // Kept till the end, not sold
                            periodCost = disks[i].price[j];
                        } else {
                            // Sold at the beginning of e + 1
                            periodCost = disks[i].price[j] - (disks[i].price[e + 1] - 100);
                        }

                        long totalCost = periodCost + dp[e + 1];
                        if (totalCost < minCost) {
                            minCost = totalCost;
                            bestNextMonth = e;
                            bestModel = disks[i].name;
                        }
                    }
                }

                dp[j] = minCost;
                choice[j] = new Choice(bestNextMonth, bestModel);
            }

            // Output results
            System.out.println(setName);
            System.out.println("Tk " + dp[1]);

            // Reconstruct path
            int curr = 1;
            ArrayList<String> usageList = new ArrayList<>();
            ArrayList<Integer> durationList = new ArrayList<>();

            while (curr <= m) {
                Choice c = choice[curr];
                int duration = c.nextMonth - curr + 1;
                
                // Merge consecutive entries of the same model if any
                if (!usageList.isEmpty() && usageList.get(usageList.size() - 1).equals(c.modelName)) {
                    int lastIdx = durationList.size() - 1;
                    durationList.set(lastIdx, durationList.get(lastIdx) + duration);
                } else {
                    usageList.add(c.modelName);
                    durationList.add(duration);
                }

                curr = c.nextMonth + 1;
            }

            for (int i = 0; i < usageList.size(); i++) {
                System.out.println(usageList.get(i) + " for " + durationList.get(i) + " month(s)");
            }
            System.out.println();
        }

        System.out.println("TheEnd");
    }
}