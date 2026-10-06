/* Node Structure
class Node
{
    int data;
    Node left, right;

    Node(int item)
    {
        data = item;
        left = right = null;
    }
} */
class Solution {

    int ans;

    int maxPathSum(Node root) {
        if (root == null) {
            return -1;
        }

        ans = Integer.MIN_VALUE;
        maxRootToLeaf(root);

        // If ans was never updated, there are fewer than 2 leaves.
        return ans == Integer.MIN_VALUE ? -1 : ans;
    }

    // Returns maximum sum from this node to any leaf below it.
    int maxRootToLeaf(Node node) {

        // Leaf node
        if (node.left == null && node.right == null) {
            return node.data;
        }

        // Only right child exists
        if (node.left == null) {
            return node.data + maxRootToLeaf(node.right);
        }

        // Only left child exists
        if (node.right == null) {
            return node.data + maxRootToLeaf(node.left);
        }

        // Both children exist
        int leftSum = maxRootToLeaf(node.left);
        int rightSum = maxRootToLeaf(node.right);

        // Path connecting two leaves through this node
        ans = Math.max(ans, leftSum + rightSum + node.data);

        // Return best path from this node to one leaf.
        return node.data + Math.max(leftSum, rightSum);
    }
}