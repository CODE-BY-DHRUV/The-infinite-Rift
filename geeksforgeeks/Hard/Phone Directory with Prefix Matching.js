import java.util.*;

class Solution {

    static class TrieNode {
        TrieNode[] child = new TrieNode[26];
        ArrayList<String> contacts = new ArrayList<>();
    }

    public ArrayList<ArrayList<String>> displayContacts(
            String[] contact, String s) {

        ArrayList<ArrayList<String>> result =
                new ArrayList<>();

        // Remove duplicates and sort contacts
        TreeSet<String> set = new TreeSet<>();

        for (String word : contact) {
            set.add(word);
        }

        TrieNode root = new TrieNode();

        // Insert sorted contacts
        for (String word : set) {
            TrieNode curr = root;

            for (char ch : word.toCharArray()) {
                int idx = ch - 'a';

                if (curr.child[idx] == null) {
                    curr.child[idx] = new TrieNode();
                }

                curr = curr.child[idx];

                // Because words are inserted in sorted order,
                // contacts will automatically be lexicographically sorted.
                curr.contacts.add(word);
            }
        }

        TrieNode curr = root;

        for (char ch : s.toCharArray()) {
            int idx = ch - 'a';

            if (curr != null && curr.child[idx] != null) {
                curr = curr.child[idx];

                result.add(new ArrayList<>(curr.contacts));
            } else {
                curr = null;

                ArrayList<String> temp = new ArrayList<>();
                temp.add("0");

                result.add(temp);
            }
        }

        return result;
    }
}