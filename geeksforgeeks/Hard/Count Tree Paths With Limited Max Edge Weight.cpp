
import java.util.*;

class Solution {

    static class DSU {
        int[] parent;
        long[] size;

        DSU(int n) {
            parent = new int[n + 1];
            size = new long[n + 1];

            for (int i = 1; i <= n; i++) {
                parent[i] = i;
                size[i] = 1;
            }
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        long union(int u, int v) {
            int pu = find(u);
            int pv = find(v);

            if (pu == pv) return 0;

            if (size[pu] < size[pv]) {
                int temp = pu;
                pu = pv;
                pv = temp;
            }

            long paths = size[pu] * size[pv];

            parent[pv] = pu;
            size[pu] += size[pv];

            return paths;
        }
    }

    public ArrayList<Integer> maximumWeight(
            int n, int[][] edges, int[] queries) {

        Arrays.sort(edges, (a, b) ->
            Integer.compare(a[2], b[2])
        );

        int q = queries.length;

        int[][] sq = new int[q][2];

        for (int i = 0; i < q; i++) {
            sq[i][0] = queries[i];
            sq[i][1] = i;
        }

        Arrays.sort(sq, (a, b) ->
            Integer.compare(a[0], b[0])
        );

        DSU dsu = new DSU(n);

        int[] ans = new int[q];

        long total = 0;
        int j = 0;

        for (int i = 0; i < q; i++) {

            int limit = sq[i][0];
            int idx = sq[i][1];

            while (j < edges.length &&
                   edges[j][2] <= limit) {

                total += dsu.union(
                    edges[j][0],
                    edges[j][1]
                );

                j++;
            }

            ans[idx] = (int) total;
        }

        ArrayList<Integer> result = new ArrayList<>();

        for (int x : ans) {
            result.add(x);
        }

        return result;
    }
}
