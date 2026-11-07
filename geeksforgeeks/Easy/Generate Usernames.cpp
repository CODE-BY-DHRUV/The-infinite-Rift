import java.util.*;

class Solution {
    public ArrayList<String> generateUsernames(String[] arr) {
        HashSet<String> used = new HashSet<>(Arrays.asList(arr));
        HashSet<String> processed = new HashSet<>();
        HashMap<String, Integer> next = new HashMap<>();

        ArrayList<String> ans = new ArrayList<>();

        for (String name : arr) {
            if (processed.add(name)) {
                ans.add(name);
                next.put(name, 1);
            } else {
                int suffix = next.get(name);

                while (used.contains(name + suffix)) {
                    suffix++;
                }

                String username = name + suffix;

                ans.add(username);
                used.add(username);
                next.put(name, suffix + 1);
            }
        }

        return ans;
    }
}