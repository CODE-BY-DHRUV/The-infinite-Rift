// class Node {
//     int data;
//     Node next;

//     Node(int val) {
//         data = val;
//         next = null;
//     }
// }




static Node removeKey(Node head, int key) {
    Node dummy = new Node(0);
    dummy.next = head;

    Node curr = dummy;

    while (curr.next != null) {
        if (curr.next.data == key) {
            curr.next = curr.next.next;
        } else {
            curr = curr.next;
        }
    }

    return dummy.next;
}

