/* Trie Node Structure
class TrieNode {
    public TrieNode[] children = new TrieNode[26];
    public boolean isEndOfWord;

    public TrieNode() {
        for (int i = 0; i < 26; ++i) {
            children[i] = null;
        }
        isEndOfWord = false;
    }
} */
class Trie {

    static class Node {
        Node[] child = new Node[26];
        boolean isEnd;
    }

    Node root = new Node();

    public void insert(String word) {
        Node curr = root;

        for (char ch : word.toCharArray()) {
            int idx = ch - 'a';

            if (curr.child[idx] == null) {
                curr.child[idx] = new Node();
            }

            curr = curr.child[idx];
        }

        curr.isEnd = true;
    }

    public boolean search(String word) {
        Node curr = root;

        for (char ch : word.toCharArray()) {
            int idx = ch - 'a';

            if (curr.child[idx] == null) {
                return false;
            }

            curr = curr.child[idx];
        }

        return curr.isEnd;
    }

    public void deleteKey(String key) {
        delete(root, key, 0);
    }

    private boolean delete(Node curr, String key, int depth) {

        if (curr == null) {
            return false;
        }

        // Reached the end of the key
        if (depth == key.length()) {

            // Key does not exist
            if (!curr.isEnd) {
                return false;
            }

            // Unmark the word
            curr.isEnd = false;

            // Delete this node if it has no children
            return hasNoChildren(curr);
        }

        int idx = key.charAt(depth) - 'a';

        if (curr.child[idx] == null) {
            // Key does not exist
            return false;
        }

        boolean deleteChild = delete(curr.child[idx], key, depth + 1);

        if (deleteChild) {
            curr.child[idx] = null;
        }

        // Current node can be removed if:
        // - it is not the end of another word
        // - it has no children
        return !curr.isEnd && hasNoChildren(curr);
    }

    private boolean hasNoChildren(Node node) {
        for (int i = 0; i < 26; i++) {
            if (node.child[i] != null) {
                return false;
            }
        }

        return true;
    }
}