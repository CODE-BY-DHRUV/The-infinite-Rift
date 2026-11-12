/* Structure of a Binary Search Tree node
class Node {
  public int data;
  public Node left;
  public Node right;

  public Node(int val) {
      data = val;
      left = right = null;
  }
};
*/


class Solution {
    public ArrayList<Integer> findCommon(Node r1, Node r2) {

        ArrayList<Integer> a = new ArrayList<>();
        ArrayList<Integer> b = new ArrayList<>();
        ArrayList<Integer> ans = new ArrayList<>();

        inorder(r1, a);
        inorder(r2, b);

        int i = 0, j = 0;

        while (i < a.size() && j < b.size()) {

            if (a.get(i).equals(b.get(j))) {
                ans.add(a.get(i));
                i++;
                j++;
            }
            else if (a.get(i) < b.get(j)) {
                i++;
            }
            else {
                j++;
            }
        }

        return ans;
    }

    private void inorder(Node root, ArrayList<Integer> list) {

        if (root == null) return;

        inorder(root.left, list);
        list.add(root.data);
        inorder(root.right, list);
    }
}
