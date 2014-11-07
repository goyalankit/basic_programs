namespace Tree {
  typedef struct Node {
    Node(int _d, Node *_left, Node *_right) :
      data(_d), left(_left), right(_right) {}

    int data;
    Node *left;
    Node *right;
  };

  Node* insertNode(Node *root, int data) {
    if (root->data <= data) {
      if (root->right == NULL) {
        root->right = new Node(data, NULL, NULL);
      } else {
        insertNode(root->right, data);
      }
    } else {
      if (root->left == NULL) {
        root->left = new Node(data, NULL, NULL);
      } else {
        insertNode(root->left, data);
      }
    }
    return root;
  }

  Node * create_binary_tree(){
    Node *root = new Node(6, NULL, NULL);
    root = insertNode(root, 7);
    root = insertNode(root, 4);
    root = insertNode(root, 3);
    root = insertNode(root, 2);
    root = insertNode(root, 12);
    root = insertNode(root, 16);
    root = insertNode(root, 22);
    root = insertNode(root, 32);
    root = insertNode(root, 62);
    root = insertNode(root, 0);

    if (root->left == NULL || root->right == NULL) {
      std::cout << "Dammit" << std::endl;
    }
    return root;
  }
}
