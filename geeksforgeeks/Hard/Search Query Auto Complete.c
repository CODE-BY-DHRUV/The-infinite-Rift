import java.util.*;

class AutoCompleteSystem {

    HashMap<String, Integer> freq;
    StringBuilder query;

    public AutoCompleteSystem(String[] sentences, int[] times) {
        freq = new HashMap<>();
        query = new StringBuilder();

        for (int i = 0; i < sentences.length; i++) {
            freq.put(sentences[i], times[i]);
        }
    }

    public List<String> input(char c) {

        // End of query
        if (c == '#') {
            String s = query.toString();

            freq.put(s, freq.getOrDefault(s, 0) + 1);

            query.setLength(0);

            return new ArrayList<>();
        }

        query.append(c);

        String prefix = query.toString();

        List<String> result = new ArrayList<>();

        // Find all sentences matching the prefix
        for (String s : freq.keySet()) {
            if (s.startsWith(prefix)) {
                result.add(s);
            }
        }

        // Sort:
        // 1. Higher frequency first
        // 2. Lexicographically smaller first
        Collections.sort(result, new Comparator<String>() {
            @Override
            public int compare(String a, String b) {

                int fa = freq.get(a);
                int fb = freq.get(b);

                if (fa != fb) {
                    return Integer.compare(fb, fa);
                }

                return a.compareTo(b);
            }
        });

        // Return maximum 3 suggestions
        if (result.size() > 3) {
            return new ArrayList<>(result.subList(0, 3));
        }

        return result;
    }
}